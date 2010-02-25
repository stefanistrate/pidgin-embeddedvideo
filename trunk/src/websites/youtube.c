#include <websites.h>

WebsiteInfo youtube = {
    "youtube",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))youtube\\.com/watch\\?(?<q1>(?<query>(([a-uw-z\\d-][\\w\\d-]*)|(v[\\w\\d-]+))(=[\\w\\d-~+%\\.]*)?|(=[\\w\\d-~+%\\.]*)))?(?<q2>[&;](?&query)?)*(?(<q1>)[&;]|(?(<q2>)[&;]|[&;]?))v=(?-i)(?<video_id>[\\w\\d-]{11})(?i)([&;](?&query)?)*(#[\\w\\d-=]*)?$",
    "<object width=\"425\" height=\"344\">"
        "<param name=\"movie\" value=\"http://www.youtube.com/v/%VIDEO_ID%&fs=1&rel=0\"></param>"
        "<param name=\"allowFullScreen\" value=\"true\"></param>"
        "<param name=\"allowscriptaccess\" value=\"always\"></param>"
        "<param name=\"wmode\" value=\"opaque\"></param>"
        "<embed src=\"http://www.youtube.com/v/%VIDEO_ID%&fs=1&rel=0\" type=\"application/x-shockwave-flash\" allowscriptaccess=\"always\" allowfullscreen=\"true\" wmode=\"opaque\" width=\"425\" height=\"344\"></embed>"
        "</object>",
    NULL
};
