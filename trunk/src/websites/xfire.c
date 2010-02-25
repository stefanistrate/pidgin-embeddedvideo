#include <websites.h>

WebsiteInfo xfire = {
    "xfire",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))xfire\\.com/video/(?<video_id>[\\w\\d]+)([/\\?#].*)?$",
    "<object width=\"425\" height=\"344\">"
        "<param name=\"wmode\" value=\"opaque\" />"
        "<embed src=\"http://media.xfire.com/swf/embedplayer.swf\" type=\"application/x-shockwave-flash\" allowscriptaccess=\"always\" allowfullscreen=\"true\" wmode=\"opaque\" width=\"425\" height=\"344\" flashvars=\"videoid=%VIDEO_ID%\"></embed>"
        "</object>",
    NULL
};
