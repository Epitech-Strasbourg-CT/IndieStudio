/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AAnimatedEntity.cpp
*/

#include "../../../include/Game/Entities/AAnimatedEntity.hpp"
#include "../../../include/Singletons/AssetsPool.hpp"

AAnimatedEntity::AAnimatedEntity(const std::string &str, int x, int y)
: AEntity(str, x, y)
{
}

irr::scene::ISceneNode *AAnimatedEntity::addAnimationNode(
	const std::string &name,
	const std::string &mesh,
	const std::string &textureName
)
{
	if (_animationsNodes.count(name) > 0)
		throw std::runtime_error("Name already taken");
	auto &im = IrrManager::getInstance();
	auto &am = AssetsPool::getInstance();
	auto m = static_cast<irr::scene::IAnimatedMesh *>(am.loadMesh(mesh));
	auto node = im.getSmgr()->addAnimatedMeshSceneNode(m);
	node->setVisible(false);
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setMaterialTexture(0, am.loadTexture(textureName));
	_animationsNodes[name] = node;
	return node;
}

void AAnimatedEntity::cleanAnimationNodes()
{
	for (auto &n : _animationsNodes)
		n.second->remove();
	_animationsNodes.clear();
}

void AAnimatedEntity::selectAnimation(const std::string &name)
{
	if (_animationsNodes.count(name) <= 0)
		throw std::runtime_error("no node with this name");
	if (_animationsNodes[name] == _node)
		return;
	if (_node != nullptr)
		_node->setVisible(false);
	_node = _animationsNodes[name];
	_node->setVisible(true);
}

