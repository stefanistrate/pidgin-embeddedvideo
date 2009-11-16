#include <websites.h>

WebsiteInfo dailymotion = {
    "dailymotion",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))dailymotion\\.com/video/(?-i)(?<video_id>[a-zA-Z\\d]+)([_/\\?#].*)?$",
    "<object width=\"420\" height=\"339\">"
        "<param name=\"movie\" value=\"http://www.dailymotion.com/swf/%VIDEO_ID%\" />"
        "<param name=\"allowFullScreen\" value=\"true\" />"
        "<param name=\"allowScriptAccess\" value=\"always\" />"
        "<embed src=\"http://www.dailymotion.com/swf/%VIDEO_ID%\" type=\"application/x-shockwave-flash\" width=\"420\" height=\"339\" allowFullScreen=\"true\" allowScriptAccess=\"always\"></embed>"
        "</object>",
    NULL
};
