*
*
*
    This is the Part3.pdf : Accomodating software dependencies.
                            by Martin Streicher

    There are 3 ways to sign an RPM package:
    1) when it is built
    2) re-sign a package that's already been signed
    3) sign an existing RPM that has no signature


    To setup the rpmbuild to use signiture do the next steps:

    1) setup gpg-agent which manages secret keys for all users:
    $ gpg-agent --daemon --enable-ssh-support \
                --write-env-file "${HOME}/.gpg-agent-info"

    2) source the following bash script to export agent environment:
    if [ -f "${HOME}/.gpg-agent-info" ]; then
        . "${HOME}/.gpg-agent-info"
        export GPG_AGENT_INFO
        export SSH_AUTH_SOCK
        export SSH_AGENT_PID
        export GPG_TTY=$(tty)
        export GPG_TTY
    fi

    3) use gpg like this:
    $ gpg --gen-key             ; to generate key
    $ gpg --list-key            ; to list the key
    $ gpg --export -a 'Mihai Vasilian' > RPM-GPG-KEY-vasilian   ; to export key

    4) edit $HOME/.rpmmacros and add 3 lines:
    %_signature    gpg
    %_gpg_path     /home/mihai/.gnupg
    %_gpg_name     Mihai Vasilian (Key for RPM) <grayasm@gmail.com>

    5) build the signed rpm package:
    $ rpmbuild -v --sign --bb --clean SPECS/sign3.spec
    Enter pass phrase:
    Pass phrase is good.
    Executing(%prep): ....
