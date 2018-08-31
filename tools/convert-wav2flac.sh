#!/bin/bash

###
#说明：有时打开wav格式音乐出现沙沙声，这是由于从CD转录到本地时，转录软件识别不出DTS格式，默认加了
#     后缀WAV，实际里面是DTS格式的，又因为DTS有版权限制一般播放器都解析不出来，所以需要用ffmpeg
#     工具进行转换
###
#brew install ffmpeg

for file in *.wav;
do
    name=$(echo $file |sed "s/\\.wav//g");
    ffmpeg -acodec dts -i "$name".wav -vn -sn -ac 2 -acodec flac "$name".flac;
    #ffmpeg -acodec dts -i "$name".wav -vn -sn -ac 2 -acodec alac "$name".m4a;
done

