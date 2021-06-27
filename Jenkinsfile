pipeline {
    stages{
        stage('Build all') {
            steps {
                sh '''#!/bin/bash -e
                echo "cmake -B build-gcc-Debug -DCMAKE_BUILD_TYPE=Debug"
                cmake -B build-gcc-Debug -DCMAKE_BUILD_TYPE=Debug
                cd build-gcc-Debug
                make -j 1
                '''
            }
        }
    }
}
