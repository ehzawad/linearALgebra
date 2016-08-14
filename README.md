# Hill Cipher

    https://en.wikipedia.org/wiki/Hill_cipher

### Build

    make

### Run

    make run

### Clean

    make clean

### Programm Output Representation
    According to Course Requirement

     PROF. DR. KHONDAKER ABDUL MALEQUE
     Faculty, AIUB
     Department of Mathematics

## Core Logic of the Program

###### Hill Class

    private:
    // user input text
    std::string inputText;
    MathUtility::VV encryptedCodeString;
    MathUtility::VV decryptedCodeString;
    // this length determine the matrix size
    size_t splitLength;

    public:
    // setter and getter of string
    void setText(void);
    // get inputText text
    std::string getText(void);
    // on the fly, it will encipher and decipher the text
    void splittingOnTheFly(MathUtility::VV&, std::string&, size_t tokens, size_t split, MathUtility::VV&, MathUtility::VV&, MathUtility::VV&);
    // just tokenize the whole string
    void tokenizer(std::string&);
    // will call the tokenizer method
    void statementToken(void);

    // this is directly store encrypted code
    void encryptedCode(MathUtility::VV&);
    void printEncryptedCode(void);
    // this is directly store decrypted code
    void decryptedCode(MathUtility::VV&);
    void printDecryptedCode(void);

