*
*
*
    This is the Part1.pdf : Building and distributing packages
                            by Martin Streicher

    A package can be build as simple user. It is not necessary to log in
    as root anymore.
    The layout for 'rpmbuild' utility is like this:

    ${any_directory}/BUILD
    ${any_directory}/BUILDROOT
    ${any_directory}/RPMS
    ${any_directory}/SOURCES
    ${any_directory}/SPECS
    ${any_directory}/SRPMS

    As of now the rpmbuild creates this layout at the top of $USER directory,
    although the rpm package we work on is in a different location. The
    default layout in $USER will however will remain empty.

    The source must be a tar.gz (apparently) and must be copied to SOURCES.
    It must be a kind of zipped tar because the rpmbuild will copy it
    in one of the other directories, untar and prepare it there.

    The .spec file is a text file and must be copied in SPECS. It contains
    the rpmbuild syntax with mix in bash syntax.

    In this sample we build wget-1.18 and install it in /opt/wget.
