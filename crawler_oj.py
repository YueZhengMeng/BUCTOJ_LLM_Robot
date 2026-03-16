import json
import os

import requests
from bs4 import BeautifulSoup

from config import CONFIG, CONTEST_URL_TEMPLATE, PROBLEM_SAVE_DIR
from utils import login_buctoj


def search_contest_by_id(session, contest_id):
    """根据比赛 ID 搜索比赛页面"""
    contest_url = CONTEST_URL_TEMPLATE.format(contest_id)

    try:
        resp = session.get(contest_url)
        resp.raise_for_status()  # 检查 HTTP 错误状态
    except requests.RequestException as e:
        print(f"❌ 请求比赛页面失败: {e}")
        return None

    soup = BeautifulSoup(resp.text, "html.parser")

    if "比赛已关闭" in soup.get_text():
        print(f"❌ 比赛已关闭：{contest_id}")
        return None

    if "比赛开始前" in soup.get_text():
        print(f"❌ 比赛开始前：{contest_id}")
        return None

    if "比赛尚未开始或私有" in soup.get_text():
        print(f"❌ 比赛尚未开始或私有：{contest_id}")
        return None

    # 判断页面是否包含“进行中”
    if "进行中" in soup.get_text():
        print(f"✅ 找到比赛，比赛链接：{contest_url}")
        return contest_url
    else:
        print("❌ 未找到正在进行的比赛或比赛不存在")
        return None


def get_contest_problem_links(session, contest_url):
    """获取比赛中的所有题目链接"""
    resp = session.get(contest_url)
    soup = BeautifulSoup(resp.text, "html.parser")

    # 匹配 href 包含 problem.php?cid= 的所有链接
    links = soup.find_all("a", href=True)
    # 使用 set 实现去重
    problem_links = set()
    for link in links:
        href = link["href"]
        if "problem.php?cid=" in href:
            full_url = requests.compat.urljoin(contest_url, href)
            problem_links.add(full_url)
    # 转为列表返回，并排序
    problem_links = list(problem_links)
    # 按照pid排序
    problem_links.sort(key=lambda x: int(x.split('=')[-1]))
    return problem_links


def extract_problem_details(session, idx, problem_url, verbose=CONFIG["verbose"]):
    """提取指定的一道题目的名称、描述、样例输入、样例输出和提示"""
    response = session.get(problem_url)
    if response.status_code != 200:
        raise Exception(f"请求失败，状态码: {response.status_code}")

    soup = BeautifulSoup(response.text, 'html.parser')

    # 标题
    title = soup.find('h1', class_='ui header').text.strip()

    # 描述
    description = soup.find('div', class_='ui bottom attached segment font-content').text.strip()

    # 样例输入
    sample_input_elem = next((h4 for h4 in soup.find_all('h4') if '样例输入' in h4.get_text(strip=True)), None)
    if sample_input_elem:
        code_block = sample_input_elem.find_next('div', class_='ui bottom attached segment font-content').find('code')
        sample_input = code_block.text.strip() if code_block else '无'
    else:
        sample_input = '无'

    # 样例输出
    sample_output_elem = next((h4 for h4 in soup.find_all('h4') if '样例输出' in h4.get_text(strip=True)), None)
    if sample_output_elem:
        code_block = sample_output_elem.find_next('div', class_='ui bottom attached segment font-content').find('code')
        sample_output = code_block.text.strip() if code_block else '无'
    else:
        sample_output = '无'

    # 提示
    hint_elem = soup.find('h4', class_='ui top attached block header', string='提示')
    if hint_elem:
        hint_div = hint_elem.find_next('div', class_='ui bottom attached segment font-content')
        hint = hint_div.get_text(strip=True) if hint_div else '无'
    else:
        hint = '无'

    # 输入说明
    input_header = soup.find('h4', string=lambda s: s and '输入' in s)
    if input_header:
        input_div = input_header.find_next_sibling('div', class_='ui bottom attached segment font-content')
        if input_div:
            paragraphs = input_div.find_all('p')
            input_description = '\n'.join(
                p.get_text(strip=True) for p in paragraphs) if paragraphs else input_div.get_text(strip=True)
        else:
            input_description = '无'
    else:
        input_description = '无'

    # 输出说明
    output_header = soup.find('h4', string=lambda s: s and '输出' in s)
    if output_header:
        output_div = output_header.find_next_sibling('div', class_='ui bottom attached segment font-content')
        if output_div:
            paragraphs = output_div.find_all('p')
            output_description = '\n'.join(
                p.get_text(strip=True) for p in paragraphs) if paragraphs else output_div.get_text(strip=True)
        else:
            output_description = '无'
    else:
        output_description = '无'

    details = {'idx': idx, 'title': title, 'description': description, 'input_description': input_description,
               'sample_input': sample_input, 'output_description': output_description, 'sample_output': sample_output,
               'hint': hint}

    # 去掉网页中多余的换行符
    for key, value in details.items():
        if isinstance(value, str):
            details[key] = value.replace("\r\n", "\n")

    # 是否打印详细的题目信息
    if verbose:
        print("\n" + "=" * 60)
        print(f"【题目 {details['idx']}】📌 标题：{details['title']}")
        print("=" * 60)

        print("\n📝 【题目描述】\n" + "-" * 60)
        print(details['description'])

        print("\n🔽 【输入说明】\n" + "-" * 60)
        print(details['input_description'])

        print("\n🔼 【输出说明】\n" + "-" * 60)
        print(details['output_description'])

        print("\n📥 【样例输入】\n" + "-" * 60)
        print(details['sample_input'])

        print("\n📤 【样例输出】\n" + "-" * 60)
        print(details['sample_output'])

        print("\n💡 【提示】\n" + "-" * 60)
        print(details['hint'])

        print("=" * 60 + "\n")

    # 保存为 JSON 文件
    filename = f"problem_{idx}.json"
    filepath = os.path.join(PROBLEM_SAVE_DIR, filename)
    with open(filepath, "w", encoding="utf-8") as f:
        json.dump(details, f, ensure_ascii=False, indent=4)

    print(f"✅ 已保存题目 {idx} 到 {filepath}")

    return details


def crawl_problems(session):
    # 获取比赛链接
    contest_id = CONFIG["contest_id"]
    contest_url = search_contest_by_id(session, contest_id)

    if not contest_url:
        exit(1)

    # 获取所有比赛题目
    problem_links = get_contest_problem_links(session, contest_url)

    # 提取题目信息，problem_id从0开始
    for idx, problem_url in enumerate(problem_links, 0):
        details_list = extract_problem_details(session, idx, problem_url)

    return details_list


if __name__ == "__main__":
    # 登录
    session = login_buctoj(CONFIG)
    # 爬取题目
    details_list = crawl_problems(session)
