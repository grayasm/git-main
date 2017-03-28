all: 27_recap

27_recap: player.cs
	mcs -out:player.exe `pkg-config --libs gtk-sharp-3.0` player.cs

clean:
	rm -v player.exe
