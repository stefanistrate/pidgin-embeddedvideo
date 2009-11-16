#include <websites.h>

WebsiteInfo collegehumor = {
    "collegehumor",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))collegehumor\\.com/video:(?<video_id>\\d+)(\\D.*)?$",
    "<object type=\"application/x-shockwave-flash\" data=\"http://www.collegehumor.com/moogaloop/moogaloop.swf?clip_id=%VIDEO_ID%&fullscreen=1\" width=\"425\" height=\"320\" >"
        "<param name=\"allowfullscreen\" value=\"true\"/>"
        "<param name=\"wmode\" value=\"transparent\"/>"
        "<param name=\"allowScriptAccess\" value=\"always\"/>"
        "<param name=\"movie\" quality=\"best\" value=\"http://www.collegehumor.com/moogaloop/moogaloop.swf?clip_id=%VIDEO_ID%&fullscreen=1\"/>"
        "<embed src=\"http://www.collegehumor.com/moogaloop/moogaloop.swf?clip_id=%VIDEO_ID%&fullscreen=1\" type=\"application/x-shockwave-flash\" wmode=\"transparent\"  width=\"425\" height=\"320\" allowfullscreen=\"true\" allowScriptAccess=\"always\"></embed>"
        "</object>",
    NULL
};
