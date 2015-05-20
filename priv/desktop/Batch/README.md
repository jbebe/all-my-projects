## Windows Batch Script, avagy szarból várat

|Tartalomjegyzék
|---
|[Előszó](#eloszo)<br>&nbsp;&nbsp;&nbsp;[Technikai előszó](#technikai)<br>&nbsp;&nbsp;&nbsp;[Szerszámok](#szerszamok)<br>[Referencia](#referencia)<br>&nbsp;&nbsp;&nbsp;[Egész számok](#egesz)<br>&nbsp;&nbsp;&nbsp;[Sztringek](#sztring)<br>&nbsp;&nbsp;&nbsp;[Konstansok](#konstans)<br>&nbsp;&nbsp;&nbsp;[Feltétel](#feltetel)<br>&nbsp;&nbsp;&nbsp;[goto](#goto)<br>&nbsp;&nbsp;&nbsp;[Ciklusok](#ciklusok)<br>&nbsp;&nbsp;&nbsp;[Függvények](#fuggvenyek) <br>&nbsp;&nbsp;&nbsp;[Áttekintés](#attekintes)<br>&nbsp;&nbsp;&nbsp;[call](#call) <br>&nbsp;&nbsp;&nbsp;[Vissza a függvényekhez](#vissza)<br>&nbsp;&nbsp;&nbsp;[Tömbök](#tombok)<br>[Batch Overtuned](#overtuned)<br>&nbsp;&nbsp;&nbsp;[Ha ebben kéne programoznom...](#haebben)<br>&nbsp;&nbsp;&nbsp;[strlen](#strlen)<br>&nbsp;&nbsp;&nbsp;[substr](#substr)<br>&nbsp;&nbsp;&nbsp;[indexof](#indexof)<br>&nbsp;&nbsp;&nbsp;[join](#join)<br>&nbsp;&nbsp;&nbsp;[Forrás, linkek](#forras)

<a name="eloszo"/>
#### Előszó
Mivel Windowson mindig is volt parancssor, nevezhetjük a legkézenfekvőbb programozási nyelvnek. 
Általában aki használta, azt se tudta, hogy használta. cd, dir, del. Ismerősek? Sokan nem is tudják,
de képesek vagyunk scripteket írni ezen parancsok felhasználásával anélkül,
hogy bármivel lefordíttatnánk, vagy értelmeztetnénk. 
(utalok itt a visual basic scriptre, amit szintén elég futtatnunk, ám az mégsem a shell része)

És hogy miért írtam meg ezt a cikket? 
A Batch elsőre egy rendkívül egyszerű nyelv, alig pár paranccsal. 
A szintaxisa azonban annyira rosszul lett megírva, hogy képesek vagyunk kibújni a nyelv szabályai alól
és saját kedvünk szerint alakíthatjuk azt. 
A cím is ezt érzékelteti. Nagyon gusztustalan, 
de érdekes és tanulságos segédfüggvényeket írni hozzá, hogy szép lassan teljes értékű programozási nyelvként működhessen.
<a name="technikai"/>
#### Technikai előszó

Ezen a nyelven látszik a legjobban az interpreter működése. 
Bizonyos eredményt pl. csak akkor érhetünk el, ha a változók behelyettesítése után megkérjük, hogy mégegyszer 
menjen át az interpreter a scriptünkön. Ekkor a jelzéssel ellátott változókat bontja ki.

Hatalmas előny, hogy legalább egész számokra lehet műveleteket végezni, 
így akár komolyabb matematikai függvényeknek is előkészítve a helyet. 

A nyelv egyes dolgokban nagyon szigorú, míg pl. egy függvény argumentumot használhatunk változónévként. 
<a name="szerszamok"/>
#### Szerszámok

* Egész típusú változók (-2147483647,2147483647)
* Stringek
* Feltételkezelés
* Ciklusok
* Exceptionök
* Goto
* Külső scriptek behívása
* változónévben szerepelhet: #$'()*+,-.?@[]_`{}~

<a name="referencia"/>
### Referencia:
<a name="egesz"/>
#### Egész típusú változók, értékadás

Név|Szimbólum|Általános|Rövidített
---|:---:|---|---
egyenlőség jel|**&#61;**|`set /a b=5`|
összeadás|**&#43;**|`set /a b=b+10`|`set /a b+=10`
kivonás|**&#45;**|`set /a b=b-7`|`set /a b-=7`
szorzás|**&#42;**|`set /a b=b*2`|`set /a b*=2`
osztás|**&#47;**|`set /a b=b/2`|`set /a b/=2`
hexadecimális|**0x**|`set /a b=0xff`|
oktális|**0**|`set /a b=07`|
bitshift (left)|**&#60;&#60;**|`set /a b="1<<3"`|`set /a "b<<=3"`
bitshift (right)|**&#62;&#62;**|`set /a b="8>>3"`|`set /a "b>>=3"`
bitenkénti nem|**~**|`set /a b=~10`|
bitenkénti vagy|**&#124;**|set /a b=10^&#124;5|set /a b^&#124;=5
bitenkénti és|**&#38;**|`set /a b=5^&3`|`set /a b^&=8`
bitenkénti kizáró vagy|**&#94;**|`set /a b=9^^4`|`set /a b^^=4`
csoportosítás|**( )**|`set /a b=5*(1+7)-5`|`set /a b+=(5-2)/7`
logikai nem|**!**|`set /a b=!1`|
negatív|**-**|`set /a b=-b`|`set /a b*=-1`
<a name="sztring"/>
#### Sztringek, értékadás, sztring változtatása

Jelenség|Felépítés|Használat
:---|---|---
Értékadás|`set változó=érték`|`set b=érték`<br>`érték`
Prompt|`set /p változó=Szöveg`|`set /p b=Szöveg`<br>`Szöveg:_`<br>`Szöveg:Szia<enter>`<br>`Szia`
Substring&nbsp;1|`set változó=%változó:~index%`|`set b=Hello World`<br>`set b=%b:~6%`<br>`World`
Substring&nbsp;2|`set változó=%változó:~index,hossz%`|`set b=Hello World`<br>`set b=%b:~0,5%`<br>`Hello`
Replace|`set %változó:keresett=lecserélt%`|`set b=Hello World`<br>`set b=%b: Wor=%`<br>`Hellold`
<a name="konstans"/>
#### Fontosabb konstansok

Név|Leírás|Példaérték
---|---|---
**%RANDOM%**|random szám<br>*uint15 (0-32767)*|12345
**%TIME%**|hh:mm:ss:nn|23:24:37.54
**%DATE%**|yyy-mm-dd|2013-07-04
**%CD%**|aktuális pozíció|C:\Users\username
<a name="feltetel"/>
#### Feltételkezelés

A feltételkezelésre a már jól bevált if-et használjuk. Kicsit bonyolultabb, mint más nyelvekben, sajnos több típusa van. 
A már eddigi is ismert módon így járhatunk el:
``` bat
if condition (
	command
) else (
	command
)
```
Opcionális a zárójel, ha csak egy parancsot adunk ki vagy összefűzzük őket & jellel.
``` bat
if 1 == 1 echo 1 and 1 are qual! & echo i'm alive
```
(Az else is opcionális, ám csak a zárójel után, vagy az if-fel egy sorba rakhatjuk, mivel nem külön utasítás)

Mint láthattuk, az egyenlőségjel egyenlőséget tesztel, 
ám minden feltételre nem használhatjuk az általános matematikai jeleket, épp ezért javasolt a == elvetése.
Helyette a Batch három betűs rövidítéseket használ:

Jel|Magyarul|Általános megfelelője
---|---|---
**equ**|egyenlő|**==**
**neq**|nem egyenlő|**!=**
**lss**|kisebb mint|**<**
**gtr**|nagyobb mint|**>**
**leq**|kisebb vagy egyenlő|**<=**
**geq**|nagyobb vagy egyenlő|**>=**

Egyszeri használatra
``` bat 
set /a computer=10
set /p user=Give me a number between 0 and 20: 
if %computer% gtr %user% (
	echo computer won
)
```
Logikai ÉS a gyakorlatban
``` bat 
set /a computer_a=10
set /a computer_b=15
set /p user=Give me a number between 0 and 20: 
if %computer_a% gtr %user% (
	if %computer_b% gtr %user% (
		echo one of the computers won
	)
)
```
Logikai VAGY a gyakorlatban
``` bat 
set /a computer_a=10
set /a computer_b=15
set /p user=Give me a number between 0 and 20: 
if %computer_a% gtr %user% (
  echo one of the computers won
) else (
	if %computer_b% gtr %user% (
		echo one of the computers won
	)
)
```
<a name="goto"/>
#### A goto

A Batch-ben olyan gyakran kell használni a goto-t mint máshol függvényhívást. Két részből áll. Maga a goto, és a label.
``` bat
goto :label

:label
	commands
```
Ha a kódunk így néz ki:
``` bat
:label
	commands
	
goto :label
```
Egy végtelen ciklust kapunk, amit nem akarunk, ezért egy konstans `:eof` hívással érhetünk azonnal a fájl végére. 
Így csak egyszer fut le.
``` bat
:label
	commands
	goto :eof
	
goto :label
```

Lássuk, hogyan használhatjuk ezt a tudást a gyakorlatban.
``` bat
@echo off
set /p choice=Do you like cookies? [yes/no] 
if %choice% equ yes (
	goto :likes
)
goto :eof

:likes
	echo Me too!
```
<a name="ciklusok"/>
#### Ciklusok

A ciklusok Batch-ben szintén sokfélék lehetnek, ahogy az if is.
*(ám nem kerülnek említésre, mert inkább fájlműveletekhez használatosak)*
Ebből is minket csak kettő érdekel, mégpedig azok, amelyek a programozáshoz szükségesek. 
*(A for cilklusban is lehagyható a zárójel, ám úgy használatos, ahogy eddig tettük)*

``` bat
for /l %%iterator in (implicit_from,step,implicit_to) do (
	command
)
```

Egy kis gyakorlat. Adjuk össze a számokat 1-től 100-ig!

``` bat
set /a sum=0
for /l %%i in (1,1,100) do (
	set /a sum+=%%i
)
```
Az előbb megtanult goto/label kombinációval hozhatjuk létre a jól ismert while ciklust.
``` bat
:loop
	commands
goto :loop
```
Számoljunk el végtelenig 1 másodperces szünetekkel
``` bat
set counter=0
:loop
	ping -n 2 127.0.0.1 >&0
	set /a counter+=1
	echo %counter%
goto :loop
```
<a name="fuggvenyek"/>
#### Függvények  ...helyett goto és subroutine
<a name="attekintes"/>
##### Áttekintés

Függvények nem léteznek a nyelvben, de bármikor hívhatunk egy címkézett fájlrészt ami úgy fog viselkedni, 
mintha csak a konzolból hívnánk parancsot. 
Elláthatjuk argumentumokkal, végiglépkedhetünk rajtuk, returnölhetünk akár több változót is.<br>
*(Ha a gyakorlatban akarjuk használni, érdemes a script testének végét egy* `goto :eof` *paranccsal lezárni,
hogy ne fusson keresztül az alatta definiált függvényeken.)*
De hogy is néz ki egy ilyen függvény?

``` bat
:function_name
	setlocal
	set input1=%1
	set input2=%2
	...
	set output=something
	...
	endlocal & set return=%output%
	goto :eof
```

Nézzük meg mi mit jelent ebben a rendetlenségben.<br>
`:function_name` Aki látott már c nyelveket, tudhatja, hogy ez egy label. Hivatkozhatunk rá, akárhonnan.<br>
`setlocal` Ez a parancs eredményezi azt, hogy ne a bat fájl törzseként kezelje a következő kódot, hanem úgy, 
mintha konzolból hívtunk volna meg egy másik parancsot. <br>
`%0-N` A függvényünk argumentumai, pontosabban:
* `%0` a függvény neve
* `%1 %2 %3`... argumentumok

`endlocal` Lezárjuk függvényt, a változók elvesznek<br>
`& return=%output%` Trükk. Ha az `endlocal` és `return=%output%` parancsokat egy sorban hajtjuk végre, 
az output változóra még hivatkozhatunk és globális térbe kerül return néven.<br>
<a name="call"/>
#### Egy kis kitérés: a call
A goto csak ugrik. A call ezzel a bizonyos setlocal-lal kooperál, hiszen meghívja, mint egy másik függvényt. 
Két fontos funkciója van a call-nak. Egyrészt külső scriptet tud behívni, és azok függvényeit futtatni, 
másrészt a lokális scriptben lévő label-ök alatt található függvényeket hívja meg. 

``` bat
call :some_function argmuments
```

Az említett külső scriptből való függvényhívást már nem lehet ilyen egyszerűen megejteni. 
Fel kell rá készíteni a fogadó könyvtárat, headert.<br>
**main.bat**
``` bat
call outer :outer_function2 argument
echo %return%
```
**outer.bat**
``` bat
call %1 %2
goto :eof

:outer_function
	setlocal
	endlocal & set return=outer function call reached
	goto :eof
:outer_function2
	setlocal
	endlocal & set return=outer2 function call reached
	goto :eof
```
Mint látható, az **outer.bat** fájlban szintén a call utasítással hívjuk meg az első argumentumot 
a második argumentum paraméterrel. Így az interpreter pontosan azt teszi amit kell, kérésünket átkötötte.
A globális térbe kerül a return-ölt változó. 
<a name="vissza"/>
##### Vissza a függvényekhez, gyakorlati példa

Írjunk egy fibonacci számgenerátort!

``` bat
@echo off
:main
	call :fibonacci 8
	set fib_result=%return%
	echo %fib_result%	
	goto :eof

:fibonacci
	setlocal
	set counter=%1
	set a=0
	set b=1
	set out=1
	:fibonacci_loop
		if %counter% gtr 1 (
			set /a out=a+b
			set /a a=b
			set /a b=out
			set /a counter-=1
			goto :fibonacci_loop
		)
	endlocal & set return=%out%
```
Látható, hogy ha a belépési részét is kvázi függvényként kezeljük a scriptünknek, sokkal átláthatóbb lesz. 
Ha egy függvénynek van visszatérési értéke, 
azonnal változóba mentjük, hogy ne vesszen el, így teljesen biztonságos, 
ha minden visszatérésnél következetesen a **return** változót használjuk.
<a name="tombok"/>
#### Tömbök

Batch-ben nincs tömb. Viszont a szerszámok paragrafus alatt megemlítettem, 
hogy mennyi karaktert elfogad ez a hanyag nyelv. Úgyhogy essünk is neki.
Ennek nincs különösebb struktúrája, egyszerűen csak rá lehet erőltetni a c stílusú tömb értékadást. 
Így rögtön a gyakorlattal kezdem.
Inicializáljunk egy 10 elemű tömböt, majd töltsük fel számjegyekkel.
``` bat
set /a array=10-1
for /l %%i in (0,1,%array%) do (
	set /a array[%%i]=%%i*%%i
)
```
Láthatjuk, hogy `array[0],array[1],array[2]` nevű változók generálódnak, míg a tömb nagysága az array változóban *pihen*. 
A kiíratáshoz már kell egy trükk. Az a bizonyos második átfutás a scripten. Ezt úgy érhetjük el, hogy 
a `setlocal` parancsot a `EnableDelayedExpansion` argumentummal használjuk. 
Lássuk, hogyan.
``` bat
setlocal EnableDelayedExpansion
set /a array=10-1
for /l %%i in (0,1,%array%) do (
	set /a array[%%i]=%%i*%%i
)
for /l %%i in (0,1,%array%) do (
	echo !array[%%i]!
)
endlocal
```
a `!érték!` jelen esetben azt jelzi az interpreternek, hogy miután átfutott a belső részen, 
egy következő scanneléssel értékelje ki. Ha nem lenne erre lehetőség, a ciklus `array[0],array[1]..`-ként iratná ki.
<a name="overtuned"/>
### Batch Overtuned
Mivel egy pár napos kalandról beszéltem és nem kívánok agyrákot kapni e nyelv lehetőségeinek kiaknázása miatt, 
csak megemlítem, mi az amit biztos lehet implementálni:
<a name="haebben"/>
##### Ha ebben kéne programoznom életem végéig (azon kívül hogy idő előtt halnék meg):
Függvény|Használat|Elmélet
---|---|---
**float**|`float foo=0.5+11.33`|a float függvény feldarabolja  az argumentumot<br>`[foo] [0.5] [+] [11.33]`<br>a két számot felbontja: úgy, hogy mindkettőnek egyforma nevezője legyen<br>`0.5 => [50,100]  11.33 => [1133,100]`<br>összeadja őket `1133+50=1183` és leoszt 100-zal, úgy hogy hátulról megkeresi  a harmadik karaktert és beilleszti a pontot `1183=>11.83`
**sqrt**|`sqrt foo=15`|`[foo] = [15]`<br>Alkalmazható implementáció:<br>`float sqrt(float m){`<br>&nbsp;&nbsp;&nbsp;&nbsp;`int i=0;`<br>&nbsp;&nbsp;&nbsp;&nbsp;`while( (i*i) <= m )`<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`i++;`<br>&nbsp;&nbsp;&nbsp;&nbsp;`i--;`<br>&nbsp;&nbsp;&nbsp;&nbsp;`float d = m - i*i;`<br>&nbsp;&nbsp;&nbsp;&nbsp;`float p=d/(2*i);`<br>&nbsp;&nbsp;&nbsp;&nbsp;`float a=i+p;`<br>&nbsp;&nbsp;&nbsp;&nbsp;`return a-(p*p)/(2*a);`<br>`}`
**sin** / **cos** / **tan**|`sin foo=pi`|...
tömb eljárások|`reverse arr_1`|...
linked list|...|...
<a name="strlen"/>
#### strlen
**Definíció:**
``` bat
:strlen
	setlocal EnableDelayedExpansion
	set temp=%~1~
	set counter=0
	:strlen_loop
	if !temp:~%counter%! neq ~ (
		set /a counter+=1
		goto :strlen_loop
	)
	endlocal & set return=%counter%
	goto :eof
```
**Használat:**
``` bat
call :strlen string
set /a size_of_string=%return%
```
<a name="substr"/>
#### substr
**Definíció:**
``` bat
:substr
	setlocal EnableDelayedExpansion
	set string=%~1
	set from=%2
	set to=%3
	
	call :strlen "%string%"
	set /a length=%return%
	set /a to -= from
	
	set output=!string:~%from%,%to%!
	
	endlocal & set return=%output%
	goto :eof
```
**Használat:**
``` bat
call :substr string 0 %i%
set stripped_string=%return%
```
<a name="indexof"/>
#### indexof
**Definíció:**
``` bat
:indexof
	setlocal EnableDelayedExpansion
	
	set string=%~1
	call :strlen "%string%"
	set /a string_length=%return%
	
	set search=%~2
	call :strlen "%search%"
	set /a search_length=%return%
	
	set /a i_length=%string_length%-%search_length%
	
	for /l %%i in (0,1,%i_length%) do (
		if "!string:~%%i,%search_length%!" equ "%search%" (
			endlocal & set return=%%i
			goto :eof
		)
	)
	endlocal & set return=-1
	goto :eof
```
**Használat:**
``` bat
call :indexof "LOREM IPSUM DOLOR SIT AMET" SUM
set position_of_sum=%return%
```
<a name="join"/>
#### join
**Definíció:**
``` bat
:join 
	setlocal
	set array_name=%1
	set /a array_size=!%1!
	set separator=%~2
	set output=
	set /a i=0
	:join_loop
		if %i% leq %array_size% (
			set output=%output%!%array_name%[%i%]!%separator%
			set /a i+=1
			goto :join_loop
		)
	endlocal & set return=%output:~0,-1%
	goto :eof
```
**Használat:**
``` bat
call :join array ","
set string_of_array=%return%
```

**Juhász Bálint**
___
<a name="forras"/>
### Forrás, linkek
* [ss64.com/nt/](http://ss64.com/nt/)
* [en.wikibooks.org/wiki/Windows_Batch_Scripting](http://en.wikibooks.org/wiki/Windows_Batch_Scripting)
* [csie.ntu.edu.tw/~r92092/ref/win32/win32scripting](http://www.csie.ntu.edu.tw/~r92092/ref/win32/win32scripting.html)
* [stackoverflow.com/questions/10166386/](http://stackoverflow.com/questions/10166386/arrays-linked-lists-and-other-data-structures-in-cmd-exe-batch-script)
* [dostips.com/DtTipsStringManipulation](http://www.dostips.com/DtTipsStringManipulation.php)

