# BuildingMod
[![Build Status](https://travis-ci.com/Theggv/BuildingMod.svg?token=MJzcNHosohyJUZJGgfnc&branch=master)](https://travis-ci.com/Theggv/BuildingMod) [![Build status](https://ci.appveyor.com/api/projects/status/a8vtx3vgbadm3ah9/branch/master?svg=true)](https://ci.appveyor.com/project/Theggv/buildingmod/branch/master)

## todo list:
- [ ] Сделать чтение с конфига
- [ ] Написать вспомогательные функции функции (UTIL_GetAimOrigin, UTIL_GetAimEdict)
- [ ] Доработать GameObject
	- [ ] Добавить состояния (can build, can't build, solid)
- [ ] Добавить для RenderComponent метод для задания и получения модели
- [ ] Реализовать IColliderComponent
	- [x] Должен хранить все edict
	- [ ] В ObjectManager добавляется новый индекс с id edict со ссылкой на GameObject
- [ ] Реализовать Pre и PostThink для взаимодействия игрока с GameObject.