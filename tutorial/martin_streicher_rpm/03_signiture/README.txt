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

    1) Create the gpg secret key
       See tutorial at: https://docs.github.com/en/authentication/managing-commit-signature-verification/generating-a-new-gpg-key

       $ gpg --full-generate-key

       Select (1) RSA and RSA (default)
       Select keysize (3072) (default)
       Select how long the key should be valid.
           0 = key does not expire

       Real name: Mihai Vasilian
       Email address: grayasm@gmail.com
       Comment: RPM Signing Key
       You selected this USER-ID:
           "Mihai Vasilian (RPM Signing Key) <grayasm@gmail.com>"

       Type a secure passphrase.
       Done.

       $ gpg --list-secret-keys
       /home/mihai/.gnupg/pubring.kbx
       ------------------------------
       sec   rsa3072 2022-10-08 [SC]
             6EE6BDF08BF51743ABE189E89C03756E10264874
       uid           [ultimate] Mihai Vasilian (RPM Signing Key) <grayasm@gmail.com>
       ssb   rsa3072 2022-10-08 [E]


       Print the GPG key ID, in ASCII armor format:
       $ gpg --armor --export 6EE6BDF08BF51743ABE189E89C03756E10264874

       Copy your GPG key, beginning with -----BEGIN PGP PUBLIC KEY BLOCK-----
       and ending with -----END PGP PUBLIC KEY BLOCK-----
       and save it as RPM-GPG-KEY-vasilian

    2) The gpg-agent should already be running. Check it with:

       $ gpg-agent --daemon
       gpg-agent: a gpg-agent is already running - not starting a new one

    3) To remove a secret key for whatever reason use:

       $ gpg --delete-secret-key 6EE6BDF08BF51743ABE189E89C03756E10264874

    4) edit $HOME/.rpmmacros and add 3 lines:
       %_signature    gpg
       %_gpg_path     /home/mihai/.gnupg
       %_gpg_name     Mihai Vasilian (RPM Signing Key) <grayasm@gmail.com>

    5) build and sign the rpm package:

      $ rpmbuild -v --bb --clean SPECS/sign3.spec

      $ rpmsign --addsign ./RPMS/x86_64/sign3-0.1-1.el7.x86_64.rpm

