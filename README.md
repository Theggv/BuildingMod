# BuildingMod
[![Build Status](https://travis-ci.com/Theggv/BuildingMod.svg?token=MJzcNHosohyJUZJGgfnc&branch=master)](https://travis-ci.com/Theggv/BuildingMod) [![Build status](https://ci.appveyor.com/api/projects/status/a8vtx3vgbadm3ah9/branch/master?svg=true)](https://ci.appveyor.com/project/Theggv/buildingmod/branch/master)

## todo list:
- [x] Сделать чтение с конфига
- [x] Написать вспомогательные функции функции (UTIL_GetAimOrigin, UTIL_GetAimEdict)
- [ ] Доработать GameObject
	- [x] Добавить состояния (can build, can't build, solid)
- [x] Добавить для RenderComponent метод для задания и получения модели
- [ ] Реализовать IColliderComponent
	- [x] Должен хранить все edict
	- [ ] В ObjectManager добавляется новый индекс с id edict со ссылкой на GameObject
- [x] Реализовать Pre и PostThink для взаимодействия игрока с GameObject.
- [ ] Utility
	- [x] Реализовать функцию для создания edict_t