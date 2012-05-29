#include <websites.h>

WebsiteInfo vimeo = {
    "vimeo",
    "^(?i)(https?://)?(\\w+\\.)?vimeo\\.com/(?<video_id>\\d+)([^\\w\\d].*)?$",
    "<iframe src=\"http://player.vimeo.com/video/%VIDEO_ID%?title=0&amp;byline=0&amp;portrait=0\" width=\"425\" height=\"239\" frameborder=\"0\" webkitAllowFullScreen mozallowfullscreen allowFullScreen></iframe>",
    NULL
};
