def buildDebugStatus = addEmbeddableBadgeConfiguration(id: "buildDebugStatus", subject: "Build Debug")
def unitTestsStatus = addEmbeddableBadgeConfiguration(id: "unitTestsStatus", subject: "Unit Tests")

pipeline {
    agent any

    stages{
        stage('Build debug') {
            steps {
                sh '''
                        cd build &&
                        cmake -D CMAKE_BUILD_TYPE=Debug .. &&
                        make
                '''
            }
        }

        stage('Unit tests') {
            steps {
                ctest 'InSearchPath'
            }
        }
    }
}
