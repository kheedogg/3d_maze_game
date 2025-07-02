미로 찾기 게임을 만들어 보려고 합니다.
아래 계획을 참고하여 코드를 완성해주세요.

* 화면 구성도
- 기본적으로 모든 화면은 3D로 입체감있게 표현합니다.
- StartPage (시작 화면) : 3D 블록에 'DoMazeGame'을 표시합니다.
- MenuSelectPage (메뉴 선택 화면) : '1인칭 모드', '3인칭 모드', '커스텀 모드' 버튼 3가지를 캐릭터가 들고 있는 화면을 구성합니다. 각 버튼에 마우스 오버 시 흔들리는 움직임을 추가합니다. 캐릭터는 해당 링크 내 소스를 참고하여 작업합니다. 
https://github.com/raysan5/raylib/blob/master/examples/models/models_bone_socket.c
필요하다면 raylib 모듈을 설치하여 다른 부분의 코드도 자유롭게 참고합니다.
- CustomMenuPage (커스텀 메뉴 생성 화면) : 원하는 width, height를 설정하고 시작점, 벽, 출구위치를 지정하여 새로운 맵을 만들 수 있도록 합니다. 지정한 정보들은 custom_game 로컬 Mysql 테이블에 Append 합니다.
- GamePlayMode1Page (첫번째 모드 게임 플레이 화면) : 1인칭 모드로 미로를 플레이할 수 있는 화면을 해당 링크 내 소스를 참고하여 작업합니다. 
https://github.com/raysan5/raylib/blob/master/examples/models/models_first_person_maze.c
필요하다면 raylib 모듈을 설치하여 다른 부분의 코드도 자유롭게 참고합니다.
- GamePlayMode2Page (두번째 모드 게임 플레이 화면) : 3인칭 모드로 미로를 플레이할 수 있는 화면을 해당 링크 내 소스를 팜고하여 작업합니다.
https://github.com/raysan5/raylib/blob/master/examples/models/models_cubicmap.c
필요하다면 raylib 모듈을 설치하여 다른 부분의 코드도 자유롭게 참고합니다.
- GamePlayCustomPage (커스텀 모드 게임 플레이 화면) : 위 화면에 모드 변경 버튼을 클릭 시 1인칭 또는 3인칭으로 모드가 변경될 수 있도록 합니다. 디폴트 설정은 1인칭으로 합니다. Mysql DB에 저장된 커스텀 모드 게임 중 랜덤으로 1가지를 가져와 플레이 합니다.
- GameStatusPage (게임 상태 페이지) : 게임 플레이 중 Esc 버튼을 누른 경우, '이어서 시작'과 '게임 종료' 중 하나를 선택할 수 있도록 합니다.
- FinishGamePage (게임 종료 페이지)

* 게임 흐름도
1. 사용자 StartPage 진입
2. 1번에서 진입 3초 후 자동으로 MenuSelectPage 진입
3. 2번에서 '1인칭 모드' 선택 시, GamePlayMode1Page 진입
4. 2번에서 '3인칭 모드' 선택 시, GamePlayMode2Pafe 진입
5. 2번에서 '커스텀 모드' 선택 시, GamePlayCustomPage 진입
6. 3,4,5번에서 Esc 버튼을 누르는 경우, GameStatusPage 진입
7. 게임 플레이 제한 시간에 도달하거나 6번에서 '게임 종료' 버튼을 누른 경우, FinishGamePage 진입
8. 6번에서 '이어서 시작' 버튼을 누른 경우, 이전 게임 페이지로 진입
8. 7번에서 진입 2초 후, 자동으로 1번 진입

* Data
- 로컬 Mysql DB를 1818번 포트로 띄웁니다.
- custom_game 테이블을 하나 생성합니다.
- custom_game 테이블은 id, width, height, start_point, end_point, wall 필드를 갖도록 지정합니다.
- 필드 타입이나 저장되는 값들은 알아서 지정하나 일관된 형태의 값들이 저장되도록 합니다.


* 게임 특징
- 게임 플레이는 방향키 버튼으로 캐럭터가 동서남북 방향으로 한칸씩 이동할 수 있도록 합니다.
- 캐릭터는 또한 스페이스로 점프, z 키로 공격(칼 휘두르기)을 할 수 있습니다.
- 캐릭터의 위치가 출구 지점에 도달 시 Success! 문구를 띄우고 제한 시간에 도달한 경우 Fail! 문구를 띄웁니다.
- 화면을 구성하는 데에 필요한 부분만을 CSS, HTML로 구성하며 그 외의 로직적인 부분은 c, nestjs, python 등 필요한 언어를 자율적으로 선택하여 사용합니다.
- 기본적으로 맵 크기와 시작점과 끝점은 랜덤으로 선택되도록합니다. 다만, 너무 가까이 위치되지 않도록 합니다.

위의 조건을 맞춰 미로 게임을 알아서 생성해주세요.
git pull이나 git push는 허락받지 않아도 알아서 자유롭게 진행해주세요.