def buildDebugStatus = addEmbeddableBadgeConfiguration(id: "buildDebugStatus", subject: "Build Debug")
def unitTestsStatus = addEmbeddableBadgeConfiguration(id: "unitTestsStatus", subject: "Unit Tests")

pipeline {
    agent any

    stages{
        stage('Build debug') {
            try {
                steps {
                    cmake arguments: '-B build-gcc-Debug', installation: 'InSearchPath'
                    cmakeBuild buildType: 'Debug', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true]]
                    buildDebugStatus.setStatus('passing')
                }
            } catch (Exception err)
            {
                buildDebugStatus.setStatus('failing')
            }
        }

        stage('Unit tests') {
            steps {
                ctest 'InSearchPath'
            }
        }
    }
}
