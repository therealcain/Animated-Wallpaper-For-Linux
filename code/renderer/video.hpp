#pragma once

#include <vlc/vlc.h>
#include <mutex>
#include <vector>
#include "../std/string_view"

#include "shader.hpp"

class Video
{
public:
    Video(std::string_view path, uint16_t width, uint16_t height);
    ~Video();

    inline auto& get_vlc_player() { return vlc_player; }

private:
    void setup_vlc(std::string_view path);
    void setup_opengl();

private:
    uint16_t width, height;
   
    struct {
        std::mutex mutex;
        bool update;
        std::vector<uint8_t> pixels_buffer;
        libvlc_instance_t* vlc;
        libvlc_media_player_t* player;
    } vlc_player;

    Shader shader;
    unsigned int texture_id;
};


