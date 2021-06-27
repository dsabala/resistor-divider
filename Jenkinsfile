def buildDebugStatus = addEmbeddableBadgeConfiguration(id: "buildDebugStatus", subject: "Build Debug")
def unitTestsStatus = addEmbeddableBadgeConfiguration(id: "unitTestsStatus", subject: "Unit Tests")

pipeline {
    agent any

    stages{
        stage('Build debug') {
            steps {
                cmake arguments: '-B build-gcc-Debug', installation: 'InSearchPath'
                cmakeBuild buildType: 'Debug', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true]]
            }
        }

        stage('Unit tests') {
            steps {
                ctest 'InSearchPath'
            }
        }
    }
}
