# Project Video Wall
---
## Hoe werkt het?
Voor het mogelijk maken van de video wall maken we gebruik van de *ffmpeg* Console applicatie. 

Momenteel wordt ffmpeg uitgevoerd door een prototype programma geschreven in *C++*, maar dit kan simpel geport worden naar een andere taal die toegang heeft tot de commandline, of zelfs een simpel bash script.

Naast het starten van ffmpeg voert dit programma ook een functie uit die *omxplayer*, de standard Raspberry pi media player, start op elke pi aangesloten op de video wall.


## ffmpeg
---
Voor het encoderen en opsplitsen van videos maken we gebruik van ffmpeg, een project dat al loopt vanaf 2000. Ffmpeg is software project dat werkt aan libraries en software rondom het verwerken van multimedia data.

#### ffmpeg, avconf en libav???
Wanneer je onderzoek doe naar ffmpeg dan kom je vast namen tegen zoals avconf en libav, zijn deze projecten het zelfde als ffmpeg? Of zijn dit totaal andere projecten?
De korte uitleg; 
Libav is een project dat is geforked uit FFmpeg, het wijzigde de naam van hun ffmpeg applicatie naar avconf.

*Libav en Ffmpeg zijn twee verschillende projecten*

### Hoe gebruik je ffmpeg?
---
Het gebruik van ffmpeg kan vrij simpel zijn, ffmpeg heeft in z'n simpelste vorm alleen een input en output locatie nodig.

```ffmpeg i- [input] [output]```

De input en output kunnen bestandslocaties zijn, UDP locaties en meer.
De volgende command leest een video bestand genaamd `sample.mp4` en verzend dit via UDP naar `udp://localhost:1234`

```ffmpeg -i C:/Videos/sample.mp4 -f mpegts udp://localhost:1234```

Voor het streamen met UDP is het nodig om een output format mee te geven
`-f mpegts` zorgt voor dat de output een *mpegts format* heeft, dit staat voor *MPEG transport stream*

Het is ook mogelijk om meer dan 1 output mee te geven.

```ffmpeg -i [input] [output1] [output2] ... [outputN]```

```
ffmpeg -i C:/Videos/sample.mp4              \
    -f mpegts udp://192.168.60.201:1234     \
    -f mpegts udp://192.168.60.202:1234     \
    C:/streams/stream01.mp4
```

### Crop
---
We gebruiken een crop filter om een kleiner gedeelte van een video frame te selecteren. Een crop filter kan mee worden gegeven aan `-filter:` per output

```
ffmpeg -i C:/Videos/sample.mp4              \
    -filter:v "crop=[width]:[height]:[x]:[y]" C:/Videos/cropped.mp4
```

Hier kan het ook handig zijn om gebruik te maken van verschillende keywords, voor dit voor nemen we aan dat de input een resolutie heeft van 1920x1080:

`iw` width van de input, `1920`

`ih` height van de input, `1080`

##### gebruik in prototype
In het prototype zijn de volgende lines te vinden
```c++
const std::string filter[] = {
    "-filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*0\" ",
    "-filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*0\" ",
    "-filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*0\" ",
    "-filter:v \"crop=iw/3:ih/2:iw/3*0:ih/2*1\" ",
    "-filter:v \"crop=iw/3:ih/2:iw/3*1:ih/2*1\" ",
    "-filter:v \"crop=iw/3:ih/2:iw/3*2:ih/2*1\" "
}
```
Dit is een array van string constante met voor elk scherm een eigen filter. Omdat de setup nu bestaat uit een wall van 3x2 even grote schermen, wordt de video opgesplitst in 3x2 gelijke delen.

`iw/3` zorgt ervoor dat de width in 3 gelijke stukken kan worden verdeeld, voor een andere setup dan 3x2 schermen, zorg ervoor dat `3` word vervangen voor het aantal schermen per rij

`ih/2` zorgt ervoor dat de height in 2 gelijke stukken kan worden verdeeld, voor een andere setup dan 3x2 schermen, zorg ervoor dat `2` word vervangen voor het aantal schermen per colom

`iw/3*x` regelt de x positie, x staat gelijk aan de x positie van je scherm in je wall setup (0 voor meest linker, 1 voor scherm ernaast, 2 voor scherm naast 1, etc...)

`iw/2*y` regelt de y positie, y staat gelijk aan de y positie van je scherm in je wall setup (0 voor meest boven, 1 voor scherm eronder, etc...)

## Hardware Acceleratie
---
### NVENC
> LET OP! Nvidia's Geforce GPU's zijn gelimiteerd tot 2 parallelle processen.

> Of met andere woorden, 2 gelijktijdige outputs.

> Een Quadro kaart is nodig voor Hardware Acceleratie **en** meer dan 2 outputs

> Zonder Hardware Acceleratie is streamen naar meer dan 6 outputs wel mogelijk

Tot nu ging het encodering process met behulp van de CPU, maar zodra je werk met hogere resoluties is het beter, en soms genoodzaakt, om over te stappen naar hardware acceleratie. Alle Nvidia kaarten met een Kepler based GPU hebben support voor NVENC, de NVidia Encoder. [Meer over NVENC.](https://en.wikipedia.org/wiki/Nvidia_NVENC "Wikipedia artikel")

Om NVENC te gebruiken moet je dit aangeven als codec *per output*

```
ffmpeg -i [input]                   \
   -c:v "h264_nvenc" [output1]      \
   -c:v "h264_nvenc" [output2]
```

## Het starten van omxplayer
Het is mogelijk om omxplayer op alle pi's tegelijk te starten, in de wallstream solution folder staat een python script `start_omx_on_wall.py`.

Dit maakt een ssh verbinding met Pi1, vervolgens wordt op de Pi een python script uitgevoerd die op alle pi's, die vermeld staan in de iplist, omxplayer start met `omxplayer udp://localhost:1234`.