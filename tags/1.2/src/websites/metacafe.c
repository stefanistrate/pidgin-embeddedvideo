#include <websites.h>

WebsiteInfo metacafe = {
    "metacafe",
    "^(?i)(https?://)?(\\w+\\.)?metacafe\\.com/watch/(?-i)(?<video_id>[\\w\\d-]+)/(?<misc1>[\\w\\d-]+)(?i)([^\\w\\d-].*)?$",
    "<embed flashVars=\"playerVars=autoPlay=no\" src=\"http://www.metacafe.com/fplayer/%VIDEO_ID%/%MISC1%.swf\" width=\"425\" height=\"240\" wmode=\"opaque\" allowFullScreen=\"true\" allowScriptAccess=\"always\" name=\"Metacafe_%VIDEO_ID%\" pluginspage=\"http://www.macromedia.com/go/getflashplayer\" type=\"application/x-shockwave-flash\"></embed>",
    NULL
};
