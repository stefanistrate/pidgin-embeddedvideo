#include <websites.h>

WebsiteInfo trilulilu_audio = {
    "trilulilu-audio",
    "^(?i)(https?://)?(\\w+\\.)?trilulilu\\.ro/(?<video_id>muzica-.*)$",
    "<iframe width=\"425\" height=\"35\" src=\"http://embed.trilulilu.ro/%VIDEO_ID%\" frameborder=\"0\" allowfullscreen></iframe>",
    NULL
};

