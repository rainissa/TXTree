Project ini dikerjakan oleh kelompok 3 (TXTree) yang beranggotakan 
1. Ashila Aulia Salwa (251511035 / ashila-AS)
2. Hasya Nadana Hakim (251511040 / shiningsstars)
3. Rainissa Azizah (251511059 / rainissa)
di bawah bimbingan Djoko Cahyo Utomo Lieharyani, S.Kom., M.MT selaku manager kelompok.

A. Setup Environment
Pastikan sudah menginstal software berikut sebelum menjalankan project ini:
1. [Visual Studio Code](https://code.visualstudio.com/) (versi terbaru)
2. [MinGW-w64](https://www.mingw-w64.org/) - GCC Compiler untuk Windows
3. Extension VS Code yang dibutuhkan (install melalui tab Extensions):
  - C/C++ (by Microsoft)
  - C/C++ Extension Pack (by Microsoft)

Langkah setup di VS Code:
1. Buka VS Code.
2. Klik File > Open Folder, lalu pilih folder project ini.
3. Buka terminal di VS Code dengan menekan Ctrl + \` atau melalui menu Terminal > New Terminal.
4. Pastikan MinGW sudah terdaftar di PATH dengan menjalankan perintah berikut di terminal VS Code:
   \`\`\`
   gcc --version
   \`\`\`
   Jika muncul versi GCC, berarti compiler sudah siap digunakan.

B. Instalasi
1. Clone repository ini melalui terminal VS Code:
   \`\`\`
   git clone https://github.com/rainissa/TXTree.git
   \`\`\`
2. Masuk ke folder project:
   \`\`\`
   cd TXTree
   \`\`\`

C. Cara Pakai
1. Buka folder project di VS Code (File > Open Folder).
2. Buka terminal VS Code dengan Ctrl + \`.
3. Compile file C menggunakan GCC di terminal VS Code:
   \`\`\`
   gcc *.c -o main
   \`\`\`
4. Jalankan program hasil compile:
   \`\`\`
   .\main.exe
   \`\`\`
5. Ikuti instruksi yang muncul di terminal.