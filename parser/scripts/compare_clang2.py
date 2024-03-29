import json
import yaml

def custom_sort(key):
    fixed_keys = ["kind", "type", "name", "value", "inner"]
    if key in fixed_keys:
        return fixed_keys.index(key)
    else:
        return len(fixed_keys)

def dict_representer(dumper, data):
    return dumper.represent_dict(sorted(data.items(), key=lambda x: sorted(data.keys(), key=custom_sort).index(x[0])))

yaml.add_representer(dict, dict_representer)

def filter_json(data):
    """
    递归过滤JSON数据中的键值。
    data: JSON数据。
    """
    if isinstance(data, dict):
        # 如果数据是一个字典，则遍历它的键和值。
        return {k2: filter_json(v2) if k2 in ['inner'] else v2  for k2, v2 in {k1:v1 for k1,v1 in data.items() if k1 in ['kind', 'type',  'name', 'value', 'inner']}.items()}
    elif isinstance(data, list):
        # 如果数据是一个列表，则遍历它的每个元素。
        return [filter_json(item) for item in data]
    else:
        # 如果数据不是一个字典或列表，则直接返回它。
        return data



# 读取JSON文件
with open('/workspace/SYsU-lang/parser/debug/ori_json.json', 'r') as f:
    data1 = json.load(f)

# 过滤JSON数据中的键值
filtered_data1 = filter_json(data1)

# 将过滤后的内容写入到新的JSON文件中
with open('/workspace/SYsU-lang/parser/debug/ori_yaml.yaml', 'w') as f:
    temp = []
    for i, line in enumerate(yaml.dump(filtered_data1,sort_keys=False).split('\n')):
        if i >  1 and i < 50:
            continue
        temp.append(line)
    f.write('\n'.join(temp))
