#include <websites.h>

#include <glib.h>
#include <curl/curl.h>

#include <debug.h>
#include <config.h>

static gchar buffer[1 << 20];
static size_t buflen = 1 << 20;

static int check(gchar *const);

WebsiteInfo trilulilu_audio = {
    "trilulilu-audio",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))trilulilu\\.ro/(?-i)(?<video_id>[\\w\\d]+/[\\w\\d]{14})([/?#].*)?$",
    "<object width=\"400\" height=\"50\">"
        "<param name=\"movie\" value=\"http://embed.trilulilu.ro/audio/%VIDEO_ID%.swf\"></param>"
        "<param name=\"allowFullScreen\" value=\"true\"></param>"
        "<param name=\"allowscriptaccess\" value=\"always\"></param>"
        "<embed src=\"http://embed.trilulilu.ro/audio/%VIDEO_ID%.swf\" type=\"application/x-shockwave-flash\" allowscriptaccess=\"always\" allowfullscreen=\"true\" width=\"400\" height=\"50\"></embed>"
        "</object>",
    &check
};

static int check(gchar *const link)
{
    CURL *curl;
    CURLcode res;
    size_t n;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, link);
        /* FIXME: Get the HTML page with curl. */
        res = curl_easy_recv(curl, buffer, buflen, &n);

        if (res == CURLE_OK) {
            buffer[n] = 0;
            if (g_regex_match_simple("var\\ current_file\\ =\\ \\{[^\\}]*\"mimetype\":\"audio\"[^\\}]*\\}",
                        buffer, 0, 0))
                return 1;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}
