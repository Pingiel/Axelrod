void simulate_games(int playerstrategy, int oppostrategy, int playerstrat[], int oppostrat[])
{
    for (int i = 0; i < MAX_GAMES; i++)
    {
        if (playerstrategy == 1)
        {
            playerstrat[i] = ACTIONS_COOPERATE;
        }
        if (playerstrategy == 2)
        {
            playerstrat[i] = ACTIONS_DEFECT;
        }
        if (playerstrategy == 3)
        {
            playerstrat[i] = rand() %2;
        }
        if (playerstrategy == 4)
        {
            if (i == 0)
            {
                playerstrat[i] = ACTIONS_COOPERATE;
            }
            else
            {
                playerstrat[i] = oppostrat[i - 1];
            }
        }
        if (playerstrategy == 5)
        {
            if (i < 2)
            {
                playerstrat[i] = ACTIONS_COOPERATE;
            }
            else
            {
                playerstrat[i] = oppostrat[i - 2];
            }
        }

        if (oppostrategy == 1)
        {
            oppostrat[i] = ACTIONS_COOPERATE;
        }
        if (oppostrategy = 2)
        {
            oppostrat[i] = ACTIONS_DEFECT;
        }
        if (oppostrategy == 3)
        {
            oppostrat[i] = rand() %2;
        }
        if (oppostrategy == 4)
        {
            if (i == 0)
            {
                oppostrategy[i] = ACTIONS_COOPERATEl;
            }
            else
            {
                oppostrategy[i] = playerstrategy[i - 1];
            }
        }
        if (oppostrategy == 5)
        {
            if (i < 2)
            {
                oppostrat[i] = ACTIONS_COOPERATE;
            }
            else
            {
                oppostrat[i] = playerstrat[i - 2];
            }
        }
    }
}