#include <websites.h>

WebsiteInfo google_video = {
    "google-video",
    "^(?i)(http://)?video\\.google\\.com/videoplay\\?docid=(?<video_id>-?\\d+)([&#].*)?$",
    "<embed id=VideoPlayback src=http://video.google.com/googleplayer.swf?docid=%VIDEO_ID%&hl=en&fs=true style=width:400px;height:326px allowFullScreen=true allowScriptAccess=always type=application/x-shockwave-flash></embed>",
    NULL
};
