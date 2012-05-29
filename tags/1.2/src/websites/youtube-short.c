#include <websites.h>

WebsiteInfo youtube_short = {
    "youtube-short",
    "^(?i)(https?://)?youtu\\.be/(?-i)(?<video_id>[\\w\\d-]{11})(?i)([^\\w\\d-].*)?$",
    "<iframe width=\"425\" height=\"240\" src=\"http://www.youtube.com/embed/%VIDEO_ID%\" frameborder=\"0\" allowfullscreen></iframe>",
    NULL
};
