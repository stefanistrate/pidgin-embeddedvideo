#include <websites.h>

WebsiteInfo yahoo_video = {
    "yahoo-video",
    "^(?i)(http://)?video\\.yahoo\\.com/watch/(?-i)(?<video_id>\\d+)/(?<misc1>[\\w\\d]+)([/\\?#].*)?$",
    "<object width=\"425\" height=\"320\">"
        "<param name=\"movie\" value=\"http://d.yimg.com/static.video.yahoo.com/yep/YV_YEP.swf?ver=2.2.46\" />"
        "<param name=\"wmode\" value=\"opaque\" />"
        "<param name=\"allowFullScreen\" value=\"true\" />"
        "<param name=\"AllowScriptAccess\" VALUE=\"always\" />"
        "<param name=\"bgcolor\" value=\"#000000\" />"
        "<param name=\"flashVars\" value=\"id=%MISC1%&vid=%VIDEO_ID%&intl=us&embed=1\" />"
        "<embed src=\"http://d.yimg.com/static.video.yahoo.com/yep/YV_YEP.swf?ver=2.2.46\" type=\"application/x-shockwave-flash\" width=\"425\" height=\"320\" wmode=\"opaque\" allowFullScreen=\"true\" AllowScriptAccess=\"always\" bgcolor=\"#000000\" flashVars=\"id=%MISC1%&vid=%VIDEO_ID%&intl=us&embed=1\" ></embed>"
        "</object>",
    NULL
};
