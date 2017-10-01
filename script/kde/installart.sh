#!/bin/bash

if [ `id -u` == 0 ]; then
	echo "don't run as root"
	exit
fi


# test new commands
# -----------------


# Install https://store.kde.org/p/1176107/  QTStep theme based on Aurora
cd /tmp
if [ -d qtstep ]; then
	rm -rfv qtstep
fi
mkdir qtstep && cd qtstep
wget https://dl.opendesktop.org/api/files/download/id/1502964222/QTStep.allcolors.allsizes.tar.gz
tar zxvf QTStep.allcolors.allsizes.tar.gz
if [ ! -d $HOME/.kde/share/apps/aurorae/themes ]; then
	mkdir -pv $HOME/.kde/share/apps/aurorae/themes
fi

rm QTStep.allcolors.allsizes.tar.gz
DIRLIST=(QTStepAntiford23p
		 QTStepAntiford27p
		 QTStepAntiford31p
		 QTStepBreeze23p
		 QTStepBreeze27p
		 QTStepBreeze31p
		 QTStepBreezeDark23p
		 QTStepBreezeDark27p
		 QTStepBreezeDark31p
		 QTStepBreezeHighContrast23p
		 QTStepBreezeHighContrast27p
		 QTStepBreezeHighContrast31p
		 QTStepBrownpunk23p
		 QTStepBrownpunk27p
		 QTStepBrownpunk31p
		 QTStepDust23p
		 QTStepDust27p
		 QTStepDust31p
		 QTStepGhost23p
		 QTStepGhost27p
		 QTStepGhost31p
		 QTStepHoneycomb23p
		 QTStepHoneycomb27p
		 QTStepHoneycomb31p
		 QTStepIndustrial23p
		 QTStepIndustrial27p
		 QTStepIndustrial31p
		 QTStepNorway23p
		 QTStepNorway27p
		 QTStepNorway31p
		 QTStepObsidianCoast23p
		 QTStepObsidianCoast27p
		 QTStepObsidianCoast31p
		 QTStepOpenStep23p
		 QTStepOpenStep27p
		 QTStepOpenStep31p
		 QTStepOxygen23p
		 QTStepOxygen27p
		 QTStepOxygen31p
		 QTStepOxygenCold23p
		 QTStepOxygenCold27p
		 QTStepOxygenCold31p
		 QTStepPlastik23p
		 QTStepPlastik27p
		 QTStepPlastik31p
		 QTStepprodukt23p
		 QTStepprodukt27p
		 QTStepprodukt31p
		 QTStepSteampunK23p
		 QTStepSteampunK27p
		 QTStepSteampunK31p
		 QTStepSteampunKLight23p
		 QTStepSteampunKLight27p
		 QTStepSteampunKLight31p
		 QTStepSteel23p
		 QTStepSteel27p
		 QTStepSteel31p
		 QTStepTeal23p
		 QTStepTeal27p
		 QTStepTeal31p
		 QTStepThinkPad23p
		 QTStepThinkPad27p
		 QTStepThinkPad31p
		 QTStepWMaker23p
		 QTStepWMaker27p
		 QTStepWMaker31p
		 QTStepWontonSoup23p
		 QTStepWontonSoup27p
		 QTStepWontonSoup31p
		 QTStepWontonSoupBrown23p
		 QTStepWontonSoupBrown27p
		 QTStepWontonSoupBrown31p
		 QTStepZion23p
		 QTStepZion27p
		 QTStepZion31p)

for dir in "${DIRLIST[@]}"; do
	if [ ! -d $HOME/.kde/share/apps/aurorae/$dir ]; then
		mv $dir $HOME/.kde/share/apps/aurorae/themes
	fi
done

cd /tmp/
rm -rfv qtstep
