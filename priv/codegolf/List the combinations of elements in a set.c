/*
	Given a set of n elements, the challenge is to write a function who lists all the combinations of k elements of in this set.
	Example:
	Set: [1, 7, 4]
	Input: 2
	Output: [1,7], [1,4], [7,4]
*/

/*
	JS - 117
*/

(a,b,c=[])=>((d=(e,f,g=[])=>f*e?g.push(e)+d(e-1,f-1,g)+g.pop
()+d(e-1,f,g):f||c.push(g.map(b=>a[b-1])))(a.length,b),c)


/*
	JS - Array method madness
*/

combination = (arr, k) =>
    Array
        .apply(0, { length: Math.pow(k+1, arr.length) })
        .map(Number.call, Number)
        .map(a => a
              .toString(arr.length)
              .split('')
              .sort()
              .filter((a, b, c) => c.indexOf(a) == b)
              .join(''))
        .filter((a, b, c) => a.length == k && c.indexOf(a) == b)
        .map(x => x.split('').map(y => arr[+y]))