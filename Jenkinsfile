pipeline {
    agent any

    stages{
        stage('Build all') {
            steps {
                cmake arguments: '-B build-gcc-Debug', installation: 'InSearchPath'
                cmakeBuild buildType: 'Debug', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true]]
            }
        }
    }
}
