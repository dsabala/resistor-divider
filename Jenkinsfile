def buildDebugStatus = addEmbeddableBadgeConfiguration(id: "buildDebugStatus", subject: "Build Debug")
def unitTestsStatus = addEmbeddableBadgeConfiguration(id: "unitTestsStatus", subject: "Unit Tests")

pipeline {
    agent any

    stages{
        stage('Build debug') {
            steps {
                script {
                    buildDebugStatus.setStatus('running')
                    try {
                        sh '''
                            cd build-gcc-Debug &&
                            cmake -D CMAKE_BUILD_TYPE=Debug .. &&
                            make
                        '''
                        buildDebugStatus.setStatus('passing')
                    } catch (Exception err) {
                        buildDebugStatus.setStatus('passing')
                    }
                }
            }
        }

        stage('Unit tests') {
            steps {
                sh '''
                    ctest
                '''
            }
        }
    }
}
