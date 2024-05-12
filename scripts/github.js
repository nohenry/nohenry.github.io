const tempNode = document.createElement('div')

async function getUserLanguagePercentages() {
    const response = await fetch('https://api.github.com/users/nohenry/repos');
    const repos = await response.json();

    const results = []
    for (const repo of repos) {
        if (!('languages_url' in repo)) continue;
        if (('fork' in repo) && repo['fork']) continue;

        try {
            results.push(fetch(repo['languages_url']).then(e => {
                if (e.ok) {
                    return e.json()
                } else {
                    return null;
                }
            }));
        } catch {
            continue;
        }
    }

    const allLanguages = {}
    const allLanguagesPercent = {}
    const allResults = await Promise.all(results);
    
    let sum = 0;
    for (const repoLangs of allResults) {
        if (repoLangs == null) continue;
        for (const languageId in repoLangs) {
            if (languageId in allLanguages) {
                allLanguages[languageId] += repoLangs[languageId];
            } else {
                allLanguages[languageId] = repoLangs[languageId];
            }
            sum += repoLangs[languageId];
        }
    }

    const languageArray = Object.keys(allLanguages).map(key => [key, allLanguages[key]])
    languageArray.sort((a, b) => b[1] - a[1])

    return [languageArray, sum];
}

function displayGithubLanguages(languages) {
    const htmlList = document.getElementById('language-list')
    for (const lang of languages[0]) {
        tempNode.innerHTML = `<div>
            <span>${lang[0]}</span><span class="float-end" style="color: #13A10E;">${Math.max(lang[1] / languages[1] * 100, 0.1).toFixed(1)}%</span>
        </div>`;
        htmlList.append(...tempNode.childNodes);
    }
}


window.addEventListener('load', async () => {
    let languages = localStorage.getItem('languages')
    if (languages) {
        languages = JSON.parse(languages)
    } else {
        languages = await getUserLanguagePercentages();
        localStorage.setItem('languages', JSON.stringify(languages));
    }
    displayGithubLanguages(languages)
})