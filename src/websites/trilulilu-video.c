#include <websites.h>

WebsiteInfo trilulilu_video = {
    "trilulilu-video",
    "^(?i)(https?://)?(\\w+\\.)?trilulilu\\.ro/(?<video_id>video-.*)$",
    "<iframe width=\"425\" height=\"366\" src=\"http://embed.trilulilu.ro/%VIDEO_ID%\" frameborder=\"0\" allowfullscreen></iframe>",
    NULL
};

