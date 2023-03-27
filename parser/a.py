import glob
import sys
import subprocess
import tarfile


def main(*argv):
    files = glob.glob("*.gz")
    files.sort()
    for filename in files:
        print(filename)
        tar = tarfile.open(filename)
        filename = filename[0:-3]
        tar.extractall(path=filename)
        tar.close()
        source = glob.glob(filename+"/SYsU-lang-*-Source")[0]
        llvm_prefix_path = subprocess.run(
            ["llvm-config", "--cmakedir"], stdout=subprocess.PIPE).stdout
        subprocess.run(["cmake", "-GNinja", "-DCMAKE_BUILD_TYPE=RelWithDebInfo",
                        "-DCMAKE_C_COMPILER=clang",
                        "-DCMAKE_CXX_COMPILER=clang++",
                        "-DCMAKE_INSTALL_PREFIX="+filename+'/sysu',
                        "-DCMAKE_PREFIX_PATH="+str(llvm_prefix_path),
                        "-DCPACK_SOURCE_IGNORE_FILES=.git/;tester/third_party/",
                        "-S"+source,
                        "-B"+filename+'/sysu/build'])
        subprocess.run(["cmake", "--build", filename+'/sysu/build'])
        subprocess.run(["cmake", "--build", filename +
                        '/sysu/build', "-t", "test"])
    return 0


if __name__ == '__main__':
    sys.exit(main(*sys.argv))
