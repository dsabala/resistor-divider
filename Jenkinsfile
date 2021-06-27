pipeline {
    stages{
        stage('Build all') {
            steps {
                sh '''
                    cmake -B build-gcc-Debug -DCMAKE_BUILD_TYPE=Debug &&
                    cd build-gcc-Debug &&
                    make -j 1
                '''
            }
        }
    }
}
