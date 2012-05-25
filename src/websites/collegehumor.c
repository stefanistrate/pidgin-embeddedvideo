#include <websites.h>

WebsiteInfo collegehumor = {
    "collegehumor",
    "^(?i)(https?://)?(\\w+\\.)?collegehumor\\.com/video/(?<video_id>\\d+)(\\D.*)?$",
    "<iframe src=\"http://www.collegehumor.com/e/%VIDEO_ID%\" width=\"425\" height=\"240\" frameborder=\"0\" webkitAllowFullScreen allowFullScreen></iframe>",
    NULL
};
