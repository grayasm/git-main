# You can build a specific target, e.g. '01_serialize' instead of 'all'
# to avoid installing missing packages (e.g. gtk-sharp-3.0)

all: 27_recap         \
     01_serialize

27_recap: player.cs
	mcs -out:player.exe `pkg-config --libs gtk-sharp-3.0` player.cs

01_serialize: 01_serialize.cs
	mcs -out:01_serialize.exe 01_serialize.cs

clean:
	rm -v player.exe
