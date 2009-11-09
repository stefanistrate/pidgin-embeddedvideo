#include <websites.h>

#include <glib.h>
#include <curl/curl.h>

static GString *buffer;

static int check(gchar *const);
static size_t save_downloaded_content(gchar *, size_t, size_t, void *);

WebsiteInfo trilulilu_image = {
    "trilulilu-image",
    "^(?i)(?<http>http://)?(?(<http>)(www\\.)?|(www\\.))trilulilu\\.ro/(?-i)(?<misc1>[\\w\\d]+)/(?<video_id>[\\w\\d]{14})([/?#].*)?$",
    "<object width=\"425\" height=\"344\">"
        "<param name=\"movie\" value=\"http://embed.trilulilu.ro/image/%MISC1%/%VIDEO_ID%.swf\"></param>"
        "<param name=\"allowFullScreen\" value=\"true\"></param>"
        "<param name=\"allowscriptaccess\" value=\"always\"></param>"
        "<embed src=\"http://embed.trilulilu.ro/image/%MISC1%/%VIDEO_ID%.swf\" type=\"application/x-shockwave-flash\" allowscriptaccess=\"always\" allowfullscreen=\"true\" width=\"425\" height=\"344\"></embed>"
        "</object>",
    &check
};

size_t save_downloaded_content(gchar *buf, size_t size, size_t nmemb, void *stream)
{
    g_string_append_len(buffer, buf, nmemb);
    return nmemb;
}

int check(gchar *const link)
{
    int valid = 0;
    CURL *curl;
    CURLcode curl_res;

    buffer = g_string_sized_new(65536);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, link);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_downloaded_content);
        curl_res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (curl_res == CURLE_OK) {
            if (g_regex_match_simple("var\\ current_file\\ =\\ \\{.*\"mimetype\":\"image\".*\\}",
                        buffer->str, 0, 0))
                valid = 1;
        }
    }

    g_string_free(buffer, FALSE);

    return valid;
}
