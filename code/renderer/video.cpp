#include "video.hpp"

#include <array>

#include <vlc/libvlc_media_player.h>
#include <glm/glm.hpp>
#include "../../libs/stb_image.h"
#include <GL/glew.h>

#include "gl_log.hpp"

static void* video_lock_callback(void* obj, void** planes)
{
    auto& vlc_player = reinterpret_cast<Video*>(obj)->get_vlc_player();
    vlc_player.mutex.lock();
    planes[0] = reinterpret_cast<void*>(vlc_player.pixels_buffer.data());
    return nullptr;
}

static void video_unlock_callback(void* obj, 
        [[maybe_unused]] void* picture, [[maybe_unused]] void* const* planes)
{
    auto& vlc_player = reinterpret_cast<Video*>(obj)->get_vlc_player();
    vlc_player.update = true;
    vlc_player.mutex.unlock();
}

static void video_display_callback(void*, void*) {}

void Video::setup_vlc(std::string_view path)
{
    // std::string_view might be a better option here.
    constexpr std::array<const char*, 2> args ={
        "--no-xlib",
        "--no-video-title-show"
    };

    vlc_player.vlc = libvlc_new(args.size(), args.data());

    libvlc_media_t* media;
    media = libvlc_media_new_path(vlc_player.vlc, path.data());
    vlc_player.player = libvlc_media_player_new_from_media(media);
    libvlc_media_release(media);

    // 3 is RGB
    vlc_player.pixels_buffer.reserve(width * height * 3);
    libvlc_video_set_callbacks(
        vlc_player.player, 
        video_lock_callback, 
        video_unlock_callback,
        video_display_callback,
        nullptr);

    libvlc_video_set_format(vlc_player.player, "RV24", width, height, width * 3);
    libvlc_media_player_play(vlc_player.player);
}

void Video::setup_opengl()
{
    shader.load("shaders/video.vs", "shaders/video.fs");
    
    glm::mat2x3 indices;
    indices[0][0] = 0; indices[0][1] = 1; indices[0][2] = 2;
    indices[1][0] = 2; indices[1][1] = 3; indices[1][2] = 1;

    glm::mat4x2 vertices;
    vertices[0][0] = 0; vertices[0][1] = 0;
    vertices[1][0] = 1; vertices[1][1] = 0;
    vertices[2][0] = 0; vertices[2][1] = 1;
    vertices[3][0] = 1; vertices[3][1] = 1;

    shader.bind();

    // Setting up the texture
    GL_LOG(glGenTextures(1, &texture_id));
    GL_LOG(glBindTexture(GL_TEXTURE_2D, texture_id));
    
    GL_LOG(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_LOG(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_LOG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_LOG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_LOG(glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL));
}

Video::Video(std::string_view path, uint16_t _width, uint16_t _height)
    : width(_width), height(_height)
{
    setup_vlc(path);
    setup_opengl();
}

Video::~Video()
{
    if(vlc_player.player != nullptr)
    {
        libvlc_media_player_stop(vlc_player.player);
        libvlc_media_player_release(vlc_player.player);
    }
}
