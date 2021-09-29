//
// Created by mattellegrino on 13/09/21.
//

#include <iostream>
#include "ScreenRecorder.h"

using namespace std;

ScreenRecorder::ScreenRecorder() {

    avdevice_register_all();
    avcodec_register_all();
    av_register_all();
}

ScreenRecorder::~ScreenRecorder(){

    avformat_close_input(&pAVFormatContext);
    if(!pAVFormatContext)
    {
        cout<<"\n file chiuso con successo";
    }
    else
    {
        cout<<"\n non sono stato in grado di chiudere il file";
        exit(1);
    }

    avformat_free_context(pAVFormatContext);
    if( !pAVFormatContext )
    {
        cout<<"\n avformat free successfully";
    }
    else
    {
        cout<<"\n unable to free avformat context";
        exit(1);
    }
}

void ScreenRecorder::CaptureVideoFrames() {


    int flag;
    int frameFinished; /* necessario a capire quando si è decodificato a sufficienza da ottenere un frame */

    int frame_index = 0;
    value = 0;

    pAVPacket = av_packet_alloc(); /* alloca un blocco in memoria di sizeof(AVPacket) bytes */
    if(pAVPacket == NULL)
    {
        cout << "Errore nell'allocazione del pacchetto";
    }

    pAVFrame = av_frame_alloc();
    if( !pAVFrame )
    {
        cout<<"\nunable to release the avframe resources";
        exit(1);
    }

    outFrame = av_frame_alloc();//Allocate an AVFrame and set its fields to default values.
    if( !outFrame )
    {
        cout<<"\nunable to release the avframe resources for outframe";
        exit(1);
    }
    outFrame->format = outAVCodecContext->pix_fmt;
    outFrame->width = outAVCodecContext->width;
    outFrame->height = outAVCodecContext-> height;

    int video_outbuf_size;
    int nbytes = av_image_get_buffer_size(
            outAVCodecContext->pix_fmt,
            outAVCodecContext->width,
            outAVCodecContext->height,
            32);
    /* ritorna i bytes necessari a salvare una immagine che abbia i parametri passati come argomento */


    uint8_t *video_outbuf = (uint8_t*)av_malloc(nbytes);

    if( video_outbuf == NULL )
    {
        cout<<"\nunable to allocate memory";
        exit(1);
    }

    value = av_image_fill_arrays(
            outFrame->data,outFrame->linesize,
            video_outbuf,
            AV_PIX_FMT_YUV420P,
            outAVCodecContext->width,
            outAVCodecContext->height,
            1);

    if(value < 0)
    {
        cout<<"\nerror in filling image array";
    }

    SwsContext* swsContext;

    swsContext = sws_getContext(pAVCodecContext->width,
                                pAVCodecContext->height,
                                pAVCodecContext->pix_fmt,
                                outAVCodecContext->width,
                                outAVCodecContext->height,
                                outAVCodecContext->pix_fmt,
                                SWS_BICUBIC,
                                NULL,NULL,NULL);


    int ii=0;
    int no_frames = 100;

    cout<<"\n enter No. of frames to capture : ";
    cin >> no_frames;

    AVPacket outPacket;
    int j=0;

    int got_picture;

    //parte aggiunta da me
    char buf[1024];
    int ret;
    FILE *f;


    while (av_read_frame(pAVFormatContext, pAVPacket) >=0)
    {

        if( ii++ == no_frames) break;

        if (pAVPacket->stream_index == VideoStreamIndx)
        {

            value = avcodec_send_packet(pAVCodecContext,pAVPacket);
            if (value == AVERROR(EAGAIN) || value == AVERROR_EOF)
                break;
            if( value < 0)
            {
                cout<<"unable to decode video";
                exit(1);
            }


            value = avcodec_receive_frame(pAVCodecContext,pAVFrame);
            if (value == AVERROR(EAGAIN) || value == AVERROR_EOF)
                break;
            if( value < 0)
            {
                cout<<"unable to decode video";
                exit(1);
            }


            if(pAVCodecContext->frame_number == 4);
            printf("saving frame %3d\n", pAVCodecContext->frame_number);
            fflush(stdout);

            value = 0;
            //frame decodificati con successo

            if (value >=0) {

                sws_scale( swsContext, pAVFrame->data, pAVFrame->linesize,0,pAVCodecContext->height,outFrame->data, outFrame->linesize);

                av_init_packet(&outPacket);
                outPacket.data = NULL;    // packet data will be allocated by the encoder
                outPacket.size = 0;

                value = 0;


                value = avcodec_send_frame(outAVCodecContext,outFrame);
                if (value == AVERROR(EAGAIN) || value == AVERROR_EOF)
                    break;
                if (value < 0) {
                    fprintf(stderr, "Error sending a frame for encoding\n");
                    exit(1);
                }

                while(value=avcodec_receive_packet(outAVCodecContext, &outPacket)!= AVERROR_EOF)
                {
                    if (value == AVERROR(EAGAIN))
                        break;
                    //   value = avcodec_receive_packet(outAVCodecContext, outPacket);

                    if(outPacket.pts != AV_NOPTS_VALUE)
                        outPacket.pts = av_rescale_q(outPacket.pts, video_st->codec->time_base, video_st->time_base);
                    if(outPacket.dts != AV_NOPTS_VALUE)
                        outPacket.dts = av_rescale_q(outPacket.dts, video_st->codec->time_base, video_st->time_base);

                    printf("Write frame %3d (size= %2d)\n", j++, outPacket.size/1000);
                    if(av_write_frame(outAVFormatContext ,&outPacket) != 0)
                    {
                        cout<<"\nerror in writing video frame";
                    }


                    // got_picturea
                    av_packet_unref(&outPacket);


                    value = av_write_trailer(outAVFormatContext);
                    if( value < 0)
                    {
                        cout<<"\nerror in writing av trailer";
                        exit(1);
                    }


                    //THIS WAS ADDED LATER

                    av_free(video_outbuf);

                }
            }
        }
    }
}

        int ScreenRecorder::openCamera() {

            value = 0;
            options= nullptr;
            pAVFormatContext = nullptr;

            pAVFormatContext= avformat_alloc_context();

            pAVInputFormat = av_find_input_format("x11grab");
            value = avformat_open_input(&pAVFormatContext, ":0.0", pAVInputFormat, NULL);

            if(value != 0)
            {
                cout<<"\n error in opening input device";
                exit(1);
            }

            /* set frame per second */
            value = av_dict_set( &options,"framerate","30",0 );
            if(value < 0)
            {
                cout<<"\nerror in setting dictionary value";
                exit(1);
            }


            value = av_dict_set( &options, "preset", "medium", 0 );
            if(value < 0)
            {
                cout<<"\nerror in setting preset values";
                exit(1);
            }


            //	value = avformat_find_stream_info(pAVFormatContext,NULL);
            if(value < 0)
            {
                cout<<"\nunable to find the stream information";
                exit(1);
            }

            VideoStreamIndx = -1;

            /* find the first video stream index . Also there is an API available to do the below operations */
            for(int i = 0; i < pAVFormatContext->nb_streams; i++ ) // find video stream posistion/index.
                {
                if( pAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO )
                {
                    VideoStreamIndx = i;
                    break;
                }

                }

            if( VideoStreamIndx == -1)
            {
                cout<<"\nunable to find the video stream index. (-1)";
                exit(1);
            }

            // assign pAVFormatContext to VideoStreamIndx
            pAVCodecContext = pAVFormatContext->streams[VideoStreamIndx]->codec;

            pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
            if( pAVCodec == NULL )
            {
                cout<<"\nunable to find the decoder";
                exit(1);
            }

            value = avcodec_open2(pAVCodecContext , pAVCodec , NULL);//Initialize the AVCodecContext to use the given AVCodec.
            if( value < 0 )
            {
                cout<<"\nunable to open the av codec";
                exit(1);
            }else
            {
                cout <<"Aperto codec file";
            }




        }

        /* initialize the video output file and its properties  */
        int ScreenRecorder::init_outputfile()
        {
            outAVFormatContext = NULL;
            value = 0;
            output_file = "../output.mp4";

            avformat_alloc_output_context2(&outAVFormatContext, NULL, NULL, output_file);
            if (!outAVFormatContext)
            {
                cout<<"\nerror in allocating av format output context";
                exit(1);
            }

            /* Returns the output format in the list of registered output formats which best matches the provided parameters, or returns NULL if there is no match. */
            output_format = av_guess_format(NULL, output_file ,NULL);
            if( !output_format )
            {
                cout<<"\nerror in guessing the video format. try with correct format";
                exit(1);
            }

            video_st = avformat_new_stream(outAVFormatContext ,NULL);
            if( !video_st )
            {
                cout<<"\nerror in creating a av format new stream";
                exit(1);
            }

            outAVCodecContext = avcodec_alloc_context3(outAVCodec);
            if( !outAVCodecContext )
            {
                cout<<"\nerror in allocating the codec contexts";
                exit(1);
            }

            /* set property of the video file */
            outAVCodecContext = video_st->codec;
            outAVCodecContext->codec_id = AV_CODEC_ID_MPEG4;// AV_CODEC_ID_MPEG4; // AV_CODEC_ID_H264 // AV_CODEC_ID_MPEG1VIDEO
            outAVCodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            outAVCodecContext->pix_fmt  = AV_PIX_FMT_YUV420P;
            outAVCodecContext->bit_rate = 400000; // 2500000
            outAVCodecContext->width = 1920;
            outAVCodecContext->height = 1080;
            outAVCodecContext->gop_size = 3;
            outAVCodecContext->max_b_frames = 2;
            outAVCodecContext->time_base.num = 1;
            outAVCodecContext->time_base.den = 30; // 15fps

            if (codec_id == AV_CODEC_ID_H264)
            {
                av_opt_set(outAVCodecContext->priv_data, "preset", "slow", 0);
            }

            outAVCodec = avcodec_find_encoder(AV_CODEC_ID_MPEG4);
            if( !outAVCodec )
            {
                cout<<"\nerror in finding the av codecs. try again with correct codec";
                exit(1);
            }

            /* Some container formats (like MP4) require global headers to be present
               Mark the encoder so that it behaves accordingly. */

            if ( outAVFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
            {
                outAVCodecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
            }

            value = avcodec_open2(outAVCodecContext, outAVCodec, NULL);
            if( value < 0)
            {
                cout<<"\nerror in opening the avcodec";
                exit(1);
            }

            /* create empty video file */
            if ( !(outAVFormatContext->flags & AVFMT_NOFILE) )
            {
                if( avio_open2(&outAVFormatContext->pb , output_file , AVIO_FLAG_WRITE ,nullptr, nullptr) < 0 )
                {
                    cout<<"\n error in creating the video file";
                    exit(1);
                }
            }

            if(!outAVFormatContext->nb_streams)
            {
                cout<<"\noutput file dose not contain any stream";
                exit(1);
            }

            /* imp: mp4 container or some advanced container file required header information*/
            value = avformat_write_header(outAVFormatContext , &options);
            if(value < 0)
            {
                cout<<"\nerror in writing the header context";
                exit(1);
            }

            /*
            // uncomment here to view the complete video file informations
            cout<<"\n\nOutput file information :\n\n";
            av_dump_format(outAVFormatContext , 0 ,output_file ,1);
            */
        }

