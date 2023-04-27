# Hola

# 프로젝트 개요
- 스마일게이트 챌린지 시즌3 ¡Hola 팀 레포지토리
- 챌린지 시즌3 주제는 **챌린지**로 언리얼 엔진을 다뤄보지 않은 5명(프로그래머4, 기획1)이 두 달간 학습과 게임 제작을 동시에 진행  
<img src="https://user-images.githubusercontent.com/54701846/176667215-961a9f96-0760-483a-a968-cecfce58fac9.png" width="450px" height="400px"/>  

## 프로젝트 시연 영상
[![Video Label](http://img.youtube.com/vi/FKvPCVWzjUg/0.jpg)](https://youtu.be/'FKvPCVWzjUg')
## 개발 엔진 및 개발 환경
### 게임 엔진 및 언어
> C++  
> 언리얼엔진  
> 언리얼엔진의 경우 C++ 코드와 블루프린트를 함께 사용
### 소스 컨트롤
> Github  
> Github Issue 및 Milestone을 이용해 일정관리  
> ~~(개발 단계에서 사용한 레포지토리에 문제가 생겨 어쩔 수 없이 삭제 후 새로 만들게 됨)~~

### 프로그램 개발 규칙
<img src="https://user-images.githubusercontent.com/54701846/176833588-c8e4d18c-964a-4e87-a682-12f9e74c9096.png" align="center" width="450" height="450" />

<img src="https://user-images.githubusercontent.com/54701846/176833619-2d1cf755-ac79-44f3-b592-8e79609683a6.png" align="center" width="450" height="300" />

<img src="https://user-images.githubusercontent.com/54701846/176833655-d4e03fc7-6efc-41d7-8494-6aeeaa384e0e.png" align="center" width="450" height="300" />


# 게임 소개
<div align="center">

|||  
|-----|-------------|
|**게임명**|The Last Hope|
|**테마**|포스트 아포칼립스|
|**장르**|3D 퍼즐 어드벤처|
|**플랫폼**|PC|
|**타겟 유저**|퍼즐 어드벤처 게임을 즐기는 유저|

</div>

-----------------------------

## 게임 배경
<img src="https://user-images.githubusercontent.com/54701846/176821534-993f5f41-0e04-41ed-b639-df198257e7e0.png" width="500" height="450" align="center" />

-----------------------------
## 조작 방식
- WASD : 전후좌우 이동
- Space : 점프
- Shift + W : 달리기
- Ctrl : 앉기
### 무기 획득 시

<img src="https://user-images.githubusercontent.com/54701846/176828970-bd87e5d1-a0e4-463e-9c6c-377221c0e45b.png" width="500" height="200"> 

- 근거리 무기
    - 마우스 좌클릭을 통해 공격 가능
    - 무기에 따라 연속 입력 시 콤보 어택 발동
- 원거리 무기(미완성)
    - 마우스 좌클릭을 통해 탄알 발사
    - 마우스 우클릭을 통해 조준(견착) 가능

-----------------------------
## 상호작용
| | |
|---|---|
|<img src="https://user-images.githubusercontent.com/54701846/176822180-abaa7134-92ea-4f1b-a3e2-bbc4567519ec.png" width="300" height="200">| <img src="https://user-images.githubusercontent.com/54701846/176822311-45d764e8-f5f3-4986-8a1a-45c9ceeaa10c.png" width="300" height="200">|

- 상호작용 물체와 근접 시 UI display
- 물체에 따라 필요 에너지 수치가 나오고 상호작용 시 에너지를 사용해야 함
-----------------------------
## Enemy
<img src="https://user-images.githubusercontent.com/54701846/176830106-a732a72f-4739-4d5a-8c8d-aba490585b46.png" width="400" height="300">

- NavMash 시스템을 이용 시야 범위에 들어올 경우 10초간 어그로

<img src="https://user-images.githubusercontent.com/54701846/176832905-3d941519-8b3a-486e-99bd-eb14480035d0.png" width="400" height="300">

- 근접 시 플레이어 공격

