pipeline {
    agent any

    stages{
        stage('Build all') {
            steps {
                cmake -B build-gcc-Debug -DCMAKE_BUILD_TYPE=Debug
                cd build-gcc-Debug
                make -j 1
            }
        }
    }
}
