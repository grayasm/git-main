all: 27_recap

27_recap: main.cs
	mcs -out:main.exe `pkg-config --libs gtk-sharp-2.0` main.cs

clean:
	rm -v main.exe
