file binary ( 0 1 ) 
|-> Executable files, Image files, Audio files, Video files, 
|   Database files ( SQLite databases, for example, are stored as 
|                    binary files, Font files, Archive files (RAR)
|-> structre : headers(signature or magic number ) blocks of metadata 
|   data , sections, 
|   hex signature for png is : 89 50 4E 47 0D 0A 1A 0A	
|-> In Network : When sending binary files over the network they may be 
|   encoded, One such encoding is Base64
|-> View : binary to Hex
|   
|   
|   
|   
|   https://en.wikipedia.org/wiki/MPEG_transport_stream
|   https://en.wikipedia.org/wiki/List_of_file_signatures
|   https://tsduck.io/download/docs/mpegts-introduction.pdf
|   https://ocw.unican.es/pluginfile.php/2825/course/section/2777/iso13818-1.pdf

Binary : 0 and 1 (base-2 number system)
bit : 0 or 1
Byte : 00000000 (group of 8 bits)
        1 byte = 8 bits
Hexadecimal : 0123456789abcdef (base-16 number system)
            1 byte = 2 hexadecimal 
            ex: hexadecimal 47 = 1 byte  = 8 bits = 01000111  = G ASCII	
                in any code hexadecimal they are preceded by 0x.

buffer : is temporary storage area
        ex : in file MPEG-ts buffer[0] = 47 hexdicemal = 1byte = 8 bits
Bitwise Operators : used to perform operations on individual bits of data


should read:
https://blog.video.ibm.com/streaming-video-tips/what-is-video-encoding-codecs-compression-techniques/
https://link.springer.com/referenceworkentry/10.1007/978-0-387-78414-4_240
https://imagekit.io/blog/video-encoding/
https://cdn.standards.iteh.ai/samples/83239/4973f67a57114579827b27c0b5624084/ISO-IEC-13818-1-2022.pdf
https://www.iso.org/obp/ui/en/
https://blog.ansi.org/iso-iec-13818-1-2023-coding-systems-mpeg-2/
https://www.cse.unsw.edu.au/~cs9519/lecture_notes_10/L1_COMP9519.pdf
https://cloudinary.com/guides/web-performance/video-encoding-how-it-works-formats-best-practices
https://patents.iec.ch/


