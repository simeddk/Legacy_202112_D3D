#pragma once

//1 Bone, 1 Frame
struct ModelKeyframeData
{
	float Frame;

	Vector3 Scale;
	Quaternion Rotation;
	Vector3 Translation;
};

//1 Bone, All Frame
struct ModelKeyframe
{
	string BoneName;
	vector<ModelKeyframeData> Transforms;
};

//All Bone, All Frame
class ModelClip
{
public:
	friend class Model;

private:
	ModelClip();
	~ModelClip();

public:
	UINT FrameCount() { return frameCount; }
	float FrameRate() { return frameRate; }

	ModelKeyframe* Keyframe(wstring name);

private:
	string name;

	UINT frameCount;
	float frameRate;

	unordered_map<wstring, ModelKeyframe*> keyframeMap;
};