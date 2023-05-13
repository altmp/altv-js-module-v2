# Commit guidelines

The commit guidelines for this project are kept very simple.

Any commit should just include anything relevant to that specific thing it is aiming to change/add/remove
and the commit title should contain `{subfolder}:` as a prefix.

For example, if you change something serverside, in the `server` directory, you prefix your commit with `server:`
and if you change something in the `tools` directory, you prefix your commit with `tools:`.

The commit title should also be kept short and descriptive, a good rule of thumb is the keep it below 90 character and just
very simply describe what you are doing. If you added a new property to the `Player` class called `maxHealth` you create a commit
called `shared: Add maxHealth property to Player`.
