#include <websites.h>

WebsiteInfo vimeo = {
    "vimeo",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))vimeo\\.com/(?<video_id>\\d+)([/\\?#].*)?$",
    "<object width=\"400\" height=\"300\">"
        "<param name=\"allowfullscreen\" value=\"true\" />"
        "<param name=\"allowscriptaccess\" value=\"always\" />"
        "<param name=\"movie\" value=\"http://vimeo.com/moogaloop.swf?clip_id=%VIDEO_ID%&amp;server=vimeo.com&amp;show_title=1&amp;show_byline=0&amp;show_portrait=0&amp;fullscreen=1\" />"
        "<embed src=\"http://vimeo.com/moogaloop.swf?clip_id=%VIDEO_ID%&amp;server=vimeo.com&amp;show_title=1&amp;show_byline=0&amp;show_portrait=0&amp;fullscreen=1\" type=\"application/x-shockwave-flash\" allowfullscreen=\"true\" allowscriptaccess=\"always\" width=\"400\" height=\"300\"></embed>"
        "</object>",
    NULL
};
