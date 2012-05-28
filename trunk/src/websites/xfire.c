#include <websites.h>

WebsiteInfo xfire = {
    "xfire",
    "^(?i)(https?://)?(\\w+\\.)?xfire\\.com/videos/(?<video_id>[\\w\\d]+)([^\\w\\d].*)?$",
    "<iframe src=\"http://beta.xfire.com/videos/%VIDEO_ID%/embed\" width=\"425\" height=\"266\" frameborder=\"0\"></iframe>",
    NULL
};
