function judge = stop_judge(m1, m2, min_d)
    fact_d = norm(m1 - m2);
    if fact_d < min_d
        judge = 1;
    else
        judge = 0;
    end

end
