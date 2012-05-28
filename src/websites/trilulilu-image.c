#include <websites.h>

WebsiteInfo trilulilu_image = {
    "trilulilu-image",
    "^(?i)(https?://)?(\\w+\\.)?trilulilu\\.ro/(?<video_id>imagini-.*)$",
    "<iframe width=\"425\" height=\"425\" src=\"http://embed.trilulilu.ro/%VIDEO_ID%\" frameborder=\"0\" allowfullscreen></iframe>",
    NULL
};

