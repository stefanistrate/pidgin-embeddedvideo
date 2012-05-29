#include <websites.h>

WebsiteInfo dailymotion = {
    "dailymotion",
    "^(?i)(https?://)?(\\w+\\.)?dailymotion\\.com/video/(?-i)(?<video_id>[a-zA-Z0-9]+)(?i)([^a-z0-9].*)?$",
    "<iframe frameborder=\"0\" width=\"425\" height=\"240\" src=\"http://www.dailymotion.com/embed/video/%VIDEO_ID%\" webkitAllowFullScreen allowFullScreen></iframe>",
    NULL
};
