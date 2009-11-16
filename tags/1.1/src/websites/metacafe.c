#include <websites.h>

WebsiteInfo metacafe = {
    "metacafe",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))metacafe\\.com/watch/(?-i)(?<video_id>\\d+)/(?<misc1>[\\w\\d]+)([/\\?#].*)?$",
    "<embed src=\"http://www.metacafe.com/fplayer/%VIDEO_ID%/%MISC1%.swf\" width=\"400\" height=\"345\" wmode=\"transparent\" pluginspage=\"http://www.macromedia.com/go/getflashplayer\" type=\"application/x-shockwave-flash\" allowFullScreen=\"true\" allowScriptAccess=\"always\" name=\"Metacafe_%VIDEO_ID%\"></embed>",
    NULL
};
