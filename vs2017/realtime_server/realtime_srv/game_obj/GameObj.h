#pragma once

#include <memory>

namespace realtime_srv
{

#define CLASS_IDENTIFICATION( inCode ) \
enum { kClassId = inCode }; \
virtual uint32_t GetClassId() const { return kClassId; } \

class ClientProxy;
class InputState;
class World;
class NetworkMgr;
class InputBitStream;
class OutputBitStream;

class GameObj : public std::enable_shared_from_this<GameObj>
{
public:
	// 'GOBJ' = 1196376650;
	CLASS_IDENTIFICATION(1196376650);

	enum EReplicationState
	{
		ERS_Pose = 1 << 0,
		EPS_AllState = ERS_Pose
	};
	virtual uint32_t GetAllStateMask() const { return EPS_AllState; }

public:

	GameObj();
	virtual ~GameObj() {}

	virtual void Update();

	virtual void Read(InputBitStream& inputStream) {}
	virtual uint32_t	Write(OutputBitStream& outputStream,
		uint32_t dirtyState) const = 0;

	void SetWorld(const std::shared_ptr<World> world) { world_ = world; }

	void SetMaster(std::shared_ptr<ClientProxy> cp);

	void SetNetworkMgr(const std::shared_ptr<NetworkMgr> networkMgr)
	{ networkMgr_ = networkMgr; }

	bool HasMaster() const { return hasMaster_; }
	std::shared_ptr<ClientProxy>	GetMaster() const { return master_.lock(); }
	void LoseMaster();

	bool IsPendingToDie() const
	{ return isPendingToDie_; }

	void SetPendingToDie();

	int			GetObjId()				const { return objId_; }
	void		SetObjId(int objId) { objId_ = objId; }

protected:

	virtual void BeforeProcessInput() {}
	virtual void AfterProcessInput() = 0;

	virtual void ProcessInput(float deltaTime,
		const std::shared_ptr<InputState>& inputState) {}

	void SetStateDirty(uint32_t repState);

protected:

	bool isPendingToDie_;
	bool hasMaster_;

	int	objId_;

	std::weak_ptr<ClientProxy> master_;
	std::shared_ptr<World> world_;
	std::shared_ptr<NetworkMgr> networkMgr_;
};

typedef std::shared_ptr< GameObj >	GameObjPtr;

}